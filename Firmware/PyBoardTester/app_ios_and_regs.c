#include <avr/io.h>
#include "hwbp_core_types.h"
#include "app_ios_and_regs.h"

/************************************************************************/
/* Configure and initialize IOs                                         */
/************************************************************************/
void init_ios(void)
{	/* Configure input pins */
	io_pin2in(&PORTA, 5, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);         // RST2
	io_pin2in(&PORTD, 4, PULL_IO_UP, SENSE_IO_EDGES_BOTH);               // SW_START
	io_pin2in(&PORTC, 2, PULL_IO_UP, SENSE_IO_EDGES_BOTH);               // SW_LED_SEQUENCE_OK
	io_pin2in(&PORTC, 3, PULL_IO_UP, SENSE_IO_EDGES_BOTH);               // SW_LED_SEQUENCE_NOK
	io_pin2in(&PORTB, 0, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);         // RESULT_0
	io_pin2in(&PORTB, 1, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);         // RESULT_1
	io_pin2in(&PORTB, 2, PULL_IO_TRISTATE, SENSE_IO_EDGES_BOTH);         // RESULT_2

	/* Configure input interrupts */

	/* Configure output pins */
	io_pin2out(&PORTD, 0, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_START
	io_pin2out(&PORTD, 1, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_RST2
	io_pin2out(&PORTD, 2, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_SUPPLY
	io_pin2out(&PORTD, 3, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_IOS
	io_pin2out(&PORTC, 0, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_PASS
	io_pin2out(&PORTC, 1, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_FAIL
	io_pin2out(&PORTC, 4, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_V_PLUS_1
	io_pin2out(&PORTC, 6, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_V_PLUS_2
	io_pin2out(&PORTC, 5, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_V_V3V_1
	io_pin2out(&PORTC, 7, OUT_IO_DIGITAL, IN_EN_IO_EN);                  // LED_V_V3V_2

	/* Initialize output pins */
	clr_LED_START;
	clr_LED_RST2;
	clr_LED_SUPPLY;
	clr_LED_IOS;
	clr_LED_PASS;
	clr_LED_FAIL;
	clr_LED_V_PLUS_1;
	clr_LED_V_PLUS_2;
	clr_LED_V_V3V_1;
	clr_LED_V_V3V_2;
}

/************************************************************************/
/* Registers' stuff                                                     */
/************************************************************************/
AppRegs app_regs;

uint8_t app_regs_type[] = {
	TYPE_U16,
	TYPE_FLOAT,
	TYPE_U16,
	TYPE_U16,
	TYPE_U16
};

uint16_t app_regs_n_elements[] = {
	1,
	8,
	1,
	1,
	1
};

uint8_t *app_regs_pointer[] = {
	(uint8_t*)(&app_regs.REG_SWITCHES),
	(uint8_t*)(app_regs.REG_READINGS),
	(uint8_t*)(&app_regs.REG_CONTROL),
	(uint8_t*)(&app_regs.REG_CONTROL_SET),
	(uint8_t*)(&app_regs.REG_CONTROL_CLEAR)
};