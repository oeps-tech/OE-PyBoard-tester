#include "sound.h"
#include "adc_filter.h"
#include "buttons.h"
#include "app_ios_and_regs.h"
#include "execution.h"
#include "analog_conversion.h"
#include "adc_calibration.h"

extern buttons_t buttons;

/************************************************************************
/ Functions to be used:
/
/   - adc_get_uV(index)
/   - adc_get_mV(index)
/   - produce_sound_new_button()
/   - produce_sound_pass()
/   - produce_sound_fail()
/
/ Variables to be used:
/
/   - buttons
/ ***********************************************************************/

/************************************************************************/
/* STATE INITS AND FUNCTION -  DON'T CHANGE THEM!!!                     */
/* ????????????????????????????????????????????????????  */
/*                                                                      */
/************************************************************************/
static s_t s = {true, true, false, 0, 0, 0};

//static void test_is_starting (void) { s.pass_or_fail = 0; }

int8_t back_to_s0 (void)
{
	s.first_run = true;
	return s.current_state * -1;
}

int8_t get_current_execution_state (void)
{
	return s.current_state;
}

int8_t get_pass_or_fail (void)
{
	return s.pass_or_fail;
}

int8_t s_template (void)
{	
	if (s.new_entry)
	{
		/* Define timeout if necessary */
		s.timeout = 1000;
		
		/* Initialize hardware */
		// ...
	}
	
	if (s.timeout_elapsed)
	{
		/* Do what is supposed when timeout elapsed */
		return back_to_s0();
	}
	
	return 0;
}


/************************************************************************/
/* USER FUNTIONS                                                        */
/* ????????????????????????????????????????????????????  */
/*                                                                      */
/************************************************************************/
void hardware_standby_configuration (void)
{
	clr_LED_START;
	clr_LED_RST2;
	clr_LED_SUPPLY;
	clr_LED_IOS;
	clr_LED_V_PLUS_1;
	clr_LED_V_PLUS_2;
	clr_LED_V_V3V_1;
	clr_LED_V_V3V_2;
	clr_LED_PASS;
	clr_LED_FAIL;
}

/************************************************************************
/ STATE 0
/ Waits for start button and start a 10 ms timeout
/ **********************************************************************/
bool first_sw_start = false;
int8_t s0 (void)
{
	if (buttons.sw_start && !first_sw_start)
	{
		first_sw_start = true;
		
		s.timeout = 10;		
	}
	
	if (s.timeout_elapsed)
	{
		first_sw_start = false;
		
		GO_TO_NEXT_STATE;
	}
	
	MAINTAIN_STATE;
}

/************************************************************************
/ STATE 1
/ Checks if the RST#2 is also down and saves the value
/ **********************************************************************/
bool rst2_ok;

int8_t s1 (void)
{
	rst2_ok = (read_RST2) ? false : true;
		
	GO_TO_NEXT_STATE;
}

/************************************************************************
/ STATE 2
/ Waits for LED sequence PASS/FAIL for 15 seconds
/ Check if the RST#2 has passed or failed
/ ? Go to next state
/ **********************************************************************/
int8_t s2 (void)
{
	if (s.new_entry)
	{
		s.timeout = 15000;
	}
	
	if (s.timeout_elapsed)
	{
		GO_TO_FAIL;
	}
	
	if (buttons.sw_led_sequence_ok)
	{
		set_LED_START;
		
		if (rst2_ok)
		{
			set_LED_RST2;
		}
		else
		{
			GO_TO_FAIL;
		}
		
		GO_TO_NEXT_STATE;
	}
	
	if (buttons.sw_led_sequence_nok)
	{
		GO_TO_FAIL;
	}
	
	MAINTAIN_STATE;
}


/************************************************************************
/ STATE 3
/ Checks voltages
/ **********************************************************************/
bool v_charge_led_pass;

int8_t s3 (void)
{
	 float v;
	 bool fail_3v3_1 = true;
	 bool fail_3v3_2 = true;
	 bool fail_Plus_1 = true;
	 bool fail_Plus_2 = true;
	
	v = get_V_3V3_1(); // 3% margin
	if (v > (3.3 * 1.03)) fail_3v3_1 = false;
	if (v < (3.3 * 0.97)) fail_3v3_1 = false;
	
	if (fail_3v3_1) set_LED_V_V3V_1;
	
	v = get_V_3V3_2(); // 3% margin
	if (v > (3.3 * 1.03)) fail_3v3_2 = false;
	if (v < (3.3 * 0.97)) fail_3v3_2 = false;
	
	if (fail_3v3_2) set_LED_V_V3V_2;
		
	v = get_V_Plus_1(); // 5% margin
	if (v > ((5.0-0.270) * 1.05)) fail_Plus_1 = false;
	if (v < ((5.0-0.270) * 0.95)) fail_Plus_1 = false;
	
	if (fail_Plus_1) set_LED_V_PLUS_1;
	
	v = get_V_Plus_2(); // 5% margin
	if (v > ((5.0-0.270) * 1.05)) fail_Plus_2 = false;
	if (v < ((5.0-0.270) * 0.95)) fail_Plus_2 = false;
	
	if (fail_Plus_2) set_LED_V_PLUS_2;
	
	if (!fail_3v3_1) GO_TO_FAIL;
	if (!fail_3v3_2) GO_TO_FAIL;
	if (!fail_Plus_1) GO_TO_FAIL;
	if (!fail_Plus_2) GO_TO_FAIL;
	
	set_LED_SUPPLY;
	
	GO_TO_NEXT_STATE;
}

/************************************************************************
/ STATE 4
/ Check IOs
/ 
/ **********************************************************************/
int8_t s4 (void)
{
	// The DUT should have 0, 0, 1 to show that the internal IO test passed.
	// If not, it failed.
	
	if (read_RESULT_0 == true) GO_TO_FAIL;
	if (read_RESULT_1 == true) GO_TO_FAIL;
	if (read_RESULT_2 == false) GO_TO_FAIL;
	
	set_LED_IOS;
	
	GO_TO_PASS;
}

/************************************************************************/
/* STATE FUNTIONS -  DON'T CHANGE THEM!!!                               */
/* ????????????????????????????????????????????????????  */
/*                                                                      */
/************************************************************************/
/* State 125 */
int8_t fail (void)
{
	if (s.new_entry)
	{
		s.pass_or_fail = -1;
		s.timeout = 4000;
		
		produce_sound_fail();
		
		set_LED_FAIL;
	}
	
	if (s.timeout_elapsed)
	{
		clr_LED_FAIL;
	
		return back_to_s0();
	}

	return 0;
}

/* State 126 */
int8_t pass (void)
{
	if (s.new_entry)
	{	
		s.pass_or_fail = 1;
		s.timeout = 2000;		
		
		produce_sound_pass();
		
		set_LED_PASS;
	}
	
	if (s.timeout_elapsed)
	{
		clr_LED_PASS;
		
		return back_to_s0();
	}
	
	return 0;
}

uint8_t state_counter = 0;
int8_t state_output;
uint8_t inter_state_interval = 0;

void state_machine (void)
{
	//int8_t state_output;
	
	if (s.first_run)
	{
		s.first_run = false;
		hardware_standby_configuration();
	}
	
	if (s.timeout)
	{
		if(--s.timeout == 0)
		{
			s.timeout_elapsed = true;
		}
	}
	
	if (inter_state_interval)
	{
		inter_state_interval--;
	}
	else
	{	
		switch (s.current_state)
		{
			case 0: s.pass_or_fail = 0;
					state_output = s0(); break;
			case 1: state_output = s1(); break;
			case 2: state_output = s2(); break;
			case 3: state_output = s3(); break;
			case 4: state_output = s4(); break;
			case 125: state_output = fail(); break;
			case 126: state_output = pass(); break;
		}
	
		if (state_output != 0)
		{
			inter_state_interval = 10;
		
			s.new_entry = true;
			s.timeout_elapsed = false;
			s.timeout = 0;
		
			s.current_state += state_output;
		}
		else
		{
			s.new_entry = false;
		}
	}
	
	
}