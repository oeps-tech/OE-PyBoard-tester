#include "hwbp_core.h"

#include "buttons.h"
#include "analog_conversion.h"
#include "adc_calibration.h"
#include "adc_filter.h"
#include "execution.h"

extern buttons_t buttons;
extern AppRegs app_regs;

void send_periodic_event (void)
{
//  	for (uint8_t i = 0; i < ADC_QUANTITY; i++)
//  	{
//  		app_regs.REG_READINGS[i] = adc_get_uV(i);
//  	}

	// V_3V3_1, V_3V3_2, V_Plus_1, V_Plus_2, SW_Start, SW_LedSequence, CurrentState, PassFail
	
	app_regs.REG_READINGS[0] = get_V_3V3_1();
	app_regs.REG_READINGS[1] = get_V_3V3_2();
	app_regs.REG_READINGS[2] = get_V_Plus_1();
	app_regs.REG_READINGS[3] = get_V_Plus_2();
		
	app_regs.REG_READINGS[4] = 0;
	app_regs.REG_READINGS[5] = 0;
		
	if (buttons.sw_start)      app_regs.REG_READINGS[4] = 1;
		
	if (buttons.sw_led_sequence_ok)    app_regs.REG_READINGS[5] = 1;
	if (buttons.sw_led_sequence_nok)   app_regs.REG_READINGS[5] = -1;
	
	app_regs.REG_READINGS[6] = get_current_execution_state();
	app_regs.REG_READINGS[7] = get_pass_or_fail();

	core_func_send_event(ADD_REG_READINGS, true);
}