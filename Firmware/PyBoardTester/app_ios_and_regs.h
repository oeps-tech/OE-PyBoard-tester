#ifndef _APP_IOS_AND_REGS_H_
#define _APP_IOS_AND_REGS_H_
#include "cpu.h"

void init_ios(void);
/************************************************************************/
/* Definition of input pins                                             */
/************************************************************************/
// RST2                   Description: 
// SW_START               Description: 
// SW_LED_SEQUENCE_OK     Description: 
// SW_LED_SEQUENCE_NOK    Description: 
// RESULT_0               Description: 
// RESULT_1               Description: 
// RESULT_2               Description: 

#define read_RST2 read_io(PORTA, 5)             // RST2
#define read_SW_START read_io(PORTD, 4)         // SW_START
#define read_SW_LED_SEQUENCE_OK read_io(PORTC, 2)// SW_LED_SEQUENCE_OK
#define read_SW_LED_SEQUENCE_NOK read_io(PORTC, 3)// SW_LED_SEQUENCE_NOK
#define read_RESULT_0 read_io(PORTB, 0)         // RESULT_0
#define read_RESULT_1 read_io(PORTB, 1)         // RESULT_1
#define read_RESULT_2 read_io(PORTB, 2)         // RESULT_2

/************************************************************************/
/* Definition of output pins                                            */
/************************************************************************/
// LED_START              Description: 
// LED_RST2               Description: 
// LED_SUPPLY             Description: 
// LED_IOS                Description: 
// LED_PASS               Description: 
// LED_FAIL               Description: 
// LED_V_PLUS_1           Description: 
// LED_V_PLUS_2           Description: 
// LED_V_V3V_1            Description: 
// LED_V_V3V_2            Description: 

/* LED_START */
#define set_LED_START set_io(PORTD, 0)
#define clr_LED_START clear_io(PORTD, 0)
#define tgl_LED_START toggle_io(PORTD, 0)
#define read_LED_START read_io(PORTD, 0)

/* LED_RST2 */
#define set_LED_RST2 set_io(PORTD, 1)
#define clr_LED_RST2 clear_io(PORTD, 1)
#define tgl_LED_RST2 toggle_io(PORTD, 1)
#define read_LED_RST2 read_io(PORTD, 1)

/* LED_SUPPLY */
#define set_LED_SUPPLY set_io(PORTD, 2)
#define clr_LED_SUPPLY clear_io(PORTD, 2)
#define tgl_LED_SUPPLY toggle_io(PORTD, 2)
#define read_LED_SUPPLY read_io(PORTD, 2)

/* LED_IOS */
#define set_LED_IOS set_io(PORTD, 3)
#define clr_LED_IOS clear_io(PORTD, 3)
#define tgl_LED_IOS toggle_io(PORTD, 3)
#define read_LED_IOS read_io(PORTD, 3)

/* LED_PASS */
#define set_LED_PASS set_io(PORTC, 0)
#define clr_LED_PASS clear_io(PORTC, 0)
#define tgl_LED_PASS toggle_io(PORTC, 0)
#define read_LED_PASS read_io(PORTC, 0)

/* LED_FAIL */
#define set_LED_FAIL set_io(PORTC, 1)
#define clr_LED_FAIL clear_io(PORTC, 1)
#define tgl_LED_FAIL toggle_io(PORTC, 1)
#define read_LED_FAIL read_io(PORTC, 1)

/* LED_V_PLUS_1 */
#define set_LED_V_PLUS_1 set_io(PORTC, 4)
#define clr_LED_V_PLUS_1 clear_io(PORTC, 4)
#define tgl_LED_V_PLUS_1 toggle_io(PORTC, 4)
#define read_LED_V_PLUS_1 read_io(PORTC, 4)

/* LED_V_PLUS_2 */
#define set_LED_V_PLUS_2 set_io(PORTC, 6)
#define clr_LED_V_PLUS_2 clear_io(PORTC, 6)
#define tgl_LED_V_PLUS_2 toggle_io(PORTC, 6)
#define read_LED_V_PLUS_2 read_io(PORTC, 6)

/* LED_V_V3V_1 */
#define set_LED_V_V3V_1 set_io(PORTC, 5)
#define clr_LED_V_V3V_1 clear_io(PORTC, 5)
#define tgl_LED_V_V3V_1 toggle_io(PORTC, 5)
#define read_LED_V_V3V_1 read_io(PORTC, 5)

/* LED_V_V3V_2 */
#define set_LED_V_V3V_2 set_io(PORTC, 7)
#define clr_LED_V_V3V_2 clear_io(PORTC, 7)
#define tgl_LED_V_V3V_2 toggle_io(PORTC, 7)
#define read_LED_V_V3V_2 read_io(PORTC, 7)


/************************************************************************/
/* Registers' structure                                                 */
/************************************************************************/
typedef struct
{
	uint16_t REG_SWITCHES;
	float REG_READINGS[8];
	uint16_t REG_CONTROL;
	uint16_t REG_CONTROL_SET;
	uint16_t REG_CONTROL_CLEAR;
} AppRegs;

/************************************************************************/
/* Registers' address                                                   */
/************************************************************************/
/* Registers */
#define ADD_REG_SWITCHES                    32 // U16    Controls the switches like they were pressed in the physical board
#define ADD_REG_READINGS                    33 // FLOAT  V_3V3_1, V_3V3_2, V_Plus_1, V_Plus_2, SW_Start, SW_LedSequence, CurrentState, PassFail
#define ADD_REG_CONTROL                     34 // U16    Controls internal signals
#define ADD_REG_CONTROL_SET                 35 // U16    Controls internal signals
#define ADD_REG_CONTROL_CLEAR               36 // U16    Controls internal signals

/************************************************************************/
/* PWM Generator registers' memory limits                               */
/*                                                                      */
/* DON'T change the APP_REGS_ADD_MIN value !!!                          */
/* DON'T change these names !!!                                         */
/************************************************************************/
/* Memory limits */
#define APP_REGS_ADD_MIN                    0x20
#define APP_REGS_ADD_MAX                    0x24
#define APP_NBYTES_OF_REG_BANK              40

/************************************************************************/
/* Registers' bits                                                      */
/************************************************************************/
#define B_SW_START                         (1<<0)       // 
#define B_SW_LED_SEQUENCE_OK               (1<<1)       // 
#define B_SW_LED_SEQUENCE_NOK              (1<<2)       // 
#define B_LED_START                        (1<<0)       // 
#define B_LED_RST2                         (1<<1)       // 
#define B_LED_SUPPLY                       (1<<2)       // 
#define B_LED_IOS                          (1<<3)       // 
#define B_LED_PASS                         (1<<4)       // 
#define B_LED_FAIL                         (1<<5)       // 
#define B_LED_V_PLUS_1                     (1<<6)       // 
#define B_LED_V_PLUS_2                     (1<<7)       // 
#define B_LED_V_V3V_1                      (1<<8)       // 
#define B_LED_V_V3V_2                      (1<<9)       // 
#define B_SOUND_WAIT_FOR_BUTTON            (1<<10)       // 
#define B_SOUND_PASS                       (1<<11)       // 
#define B_SOUND_FAIL                       (1<<12)       // 

#endif /* _APP_REGS_H_ */