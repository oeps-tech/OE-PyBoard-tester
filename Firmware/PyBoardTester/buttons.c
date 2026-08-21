#include "buttons.h"
#include "cpu.h"
#include "app_ios_and_regs.h"

void init_buttons_timer (void)
{
	/* Initialize a 5 ms timer to handle the buttons */
	timer_type0_enable(&TCC0, TIMER_PRESCALER_DIV1024, 156, INT_LEVEL_LOW);
}

static buttons_t buttons_previous;
static buttons_t buttons_current;
buttons_t buttons;

buttons_t buttons_from_registers;
buttons_timeout_t buttons_from_registers_timeout;

ISR(TCC0_OVF_vect, ISR_NAKED)
{
	buttons_current.sw_start = !read_SW_START;	
				
	buttons_current.sw_led_sequence_ok = !read_SW_LED_SEQUENCE_OK;
	buttons_current.sw_led_sequence_nok = !read_SW_LED_SEQUENCE_NOK;
	
	if (buttons_current.sw_start == buttons_previous.sw_start) buttons.sw_start = buttons_from_registers.sw_start ? true : buttons_current.sw_start;
	if (buttons_from_registers_timeout.sw_start) buttons_from_registers_timeout.sw_start--;
	else buttons_from_registers.sw_start = false;
	
	if (buttons_current.sw_led_sequence_ok == buttons_previous.sw_led_sequence_ok) buttons.sw_led_sequence_ok = buttons_from_registers.sw_led_sequence_ok ? true : buttons_current.sw_led_sequence_ok;
	if (buttons_from_registers_timeout.sw_led_sequence_ok) buttons_from_registers_timeout.sw_led_sequence_ok--;
	else buttons_from_registers.sw_led_sequence_ok = false;
	
	if (buttons_current.sw_led_sequence_nok == buttons_previous.sw_led_sequence_nok) buttons.sw_led_sequence_nok = buttons_from_registers.sw_led_sequence_nok ? true : buttons_current.sw_led_sequence_nok;
	if (buttons_from_registers_timeout.sw_led_sequence_nok) buttons_from_registers_timeout.sw_led_sequence_nok--;
	else buttons_from_registers.sw_led_sequence_nok = false;
	
	buttons_previous = buttons_current;
	
	reti();
}
