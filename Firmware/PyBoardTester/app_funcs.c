#include "app_funcs.h"
#include "app_ios_and_regs.h"
#include "hwbp_core.h"

#include "buttons.h"
#include "sound.h"


/************************************************************************/
/* Create pointers to functions                                         */
/************************************************************************/
extern AppRegs app_regs;

void (*app_func_rd_pointer[])(void) = {
	&app_read_REG_SWITCHES,
	&app_read_REG_READINGS,
	&app_read_REG_CONTROL,
	&app_read_REG_CONTROL_SET,
	&app_read_REG_CONTROL_CLEAR
};

bool (*app_func_wr_pointer[])(void*) = {
	&app_write_REG_SWITCHES,
	&app_write_REG_READINGS,
	&app_write_REG_CONTROL,
	&app_write_REG_CONTROL_SET,
	&app_write_REG_CONTROL_CLEAR
};


/************************************************************************/
/* REG_SWITCHES                                                         */
/************************************************************************/
extern buttons_t buttons_from_registers;
extern buttons_timeout_t buttons_from_registers_timeout;

void app_read_REG_SWITCHES(void) {}
bool app_write_REG_SWITCHES(void *a)
{
	uint16_t reg = *((uint16_t*)a);
	
	if (reg & B_SW_START) { buttons_from_registers.sw_start = true; buttons_from_registers_timeout.sw_start = BUTTONS_TIMEOUT; }
	
	if (reg & B_SW_LED_SEQUENCE_OK) { buttons_from_registers.sw_led_sequence_ok = true; buttons_from_registers_timeout.sw_led_sequence_ok = BUTTONS_TIMEOUT; }
	if (reg & B_SW_LED_SEQUENCE_NOK) { buttons_from_registers.sw_led_sequence_nok = true; buttons_from_registers_timeout.sw_led_sequence_nok = BUTTONS_TIMEOUT; }
		
	app_regs.REG_SWITCHES = reg;
	return true;
}


/************************************************************************/
/* REG_READINGS                                                         */
/************************************************************************/
// This register is an array with 8 positions
void app_read_REG_READINGS(void) {}
bool app_write_REG_READINGS(void *a)
{
	float *reg = ((float*)a);

	app_regs.REG_READINGS[0] = reg[0];
	return true;
}


/************************************************************************/
/* REG_CONTROL                                                          */
/************************************************************************/
void app_read_REG_CONTROL(void) {}
bool app_write_REG_CONTROL(void *a)
{
	uint16_t reg = *((uint16_t*)a);
	
	if (reg & B_LED_START) {set_LED_START;} else {clr_LED_START;}
	if (reg & B_LED_RST2) {set_LED_RST2;} else {clr_LED_RST2;}
	if (reg & B_LED_SUPPLY) {set_LED_SUPPLY;} else {clr_LED_SUPPLY;}
	if (reg & B_LED_IOS) {set_LED_IOS;} else {clr_LED_IOS;}
	if (reg & B_LED_PASS) {set_LED_PASS;} else {clr_LED_PASS;}
	if (reg & B_LED_FAIL) {set_LED_FAIL;} else {clr_LED_FAIL;}
	if (reg & B_LED_V_PLUS_1) {set_LED_V_PLUS_1;} else {clr_LED_V_PLUS_1;}
	if (reg & B_LED_V_PLUS_2) {set_LED_V_PLUS_2;} else {clr_LED_V_PLUS_2;}
	if (reg & B_LED_V_V3V_1) {set_LED_V_V3V_1;} else {clr_LED_V_V3V_1;}
	if (reg & B_LED_V_V3V_2) {set_LED_V_V3V_2;} else {clr_LED_V_V3V_2;}
		
	if (reg & B_SOUND_WAIT_FOR_BUTTON) {produce_sound_new_button();}
	if (reg & B_SOUND_PASS) {produce_sound_pass();}
	if (reg & B_SOUND_FAIL) {produce_sound_fail();}

	app_regs.REG_CONTROL = reg;
	return true;
}


/************************************************************************/
/* REG_CONTROL_SET                                                      */
/************************************************************************/
void app_read_REG_CONTROL_SET(void)
{
	//app_regs.REG_CONTROL_SET = 0;

}

bool app_write_REG_CONTROL_SET(void *a)
{
	uint16_t reg = *((uint16_t*)a);
	
	if (reg & B_LED_START) {set_LED_START;}
	if (reg & B_LED_RST2) {set_LED_RST2;}
	if (reg & B_LED_SUPPLY) {set_LED_SUPPLY;}
	if (reg & B_LED_IOS) {set_LED_IOS;}
	if (reg & B_LED_PASS) {set_LED_PASS;}
	if (reg & B_LED_FAIL) {set_LED_FAIL;}
	if (reg & B_LED_V_PLUS_1) {set_LED_V_PLUS_1;}
	if (reg & B_LED_V_PLUS_2) {set_LED_V_PLUS_2;}
	if (reg & B_LED_V_V3V_1) {set_LED_V_V3V_1;}
	if (reg & B_LED_V_V3V_2) {set_LED_V_V3V_2;}

		
	if (reg & B_SOUND_WAIT_FOR_BUTTON) {produce_sound_new_button();}
	if (reg & B_SOUND_PASS) {produce_sound_pass();}
	if (reg & B_SOUND_FAIL) {produce_sound_fail();}

	app_regs.REG_CONTROL_SET = reg;
	return true;
}


/************************************************************************/
/* REG_CONTROL_CLEAR                                                    */
/************************************************************************/
void app_read_REG_CONTROL_CLEAR(void)
{
	//app_regs.REG_CONTROL_CLEAR = 0;

}

bool app_write_REG_CONTROL_CLEAR(void *a)
{
	uint16_t reg = *((uint16_t*)a);
	
	if (reg & B_LED_START) {clr_LED_START;}
	if (reg & B_LED_RST2) {clr_LED_RST2;}
	if (reg & B_LED_SUPPLY) {clr_LED_SUPPLY;}
	if (reg & B_LED_IOS) {clr_LED_IOS;}
	if (reg & B_LED_PASS) {clr_LED_PASS;}
	if (reg & B_LED_FAIL) {clr_LED_FAIL;}
	if (reg & B_LED_V_PLUS_1) {clr_LED_V_PLUS_1;}
	if (reg & B_LED_V_PLUS_2) {clr_LED_V_PLUS_2;}
	if (reg & B_LED_V_V3V_1) {clr_LED_V_V3V_1;}
	if (reg & B_LED_V_V3V_2) {clr_LED_V_V3V_2;}


	app_regs.REG_CONTROL_CLEAR = reg;
	return true;
}