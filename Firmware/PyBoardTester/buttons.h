#ifndef _BUTTONS_H
#define _BUTTONS_H
#include <avr/io.h>

#include "cpu.h"
#include "app_ios_and_regs.h"

#define BUTTONS_TIMEOUT 400/5 // 400 ms

typedef struct 
{
	bool sw_start;
	bool sw_led_sequence_ok;
	bool sw_led_sequence_nok;
} buttons_t;

typedef struct
{
	uint8_t sw_start;
	uint8_t sw_led_sequence_ok;
	uint8_t sw_led_sequence_nok;
} buttons_timeout_t;

void init_buttons_timer (void);

#endif /* _BUTTONS_H */