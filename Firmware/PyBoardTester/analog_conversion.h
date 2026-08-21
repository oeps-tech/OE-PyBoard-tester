#ifndef _ANALOG_CONVERSION_H_
#define _ANALOG_CONVERSION_H_

#include "adc_filter.h"

#define get_V_3V3_1()  (adc_get_uV(1) / ((5.1/(10+5.1))*1000000.0))
#define get_V_3V3_2()  (adc_get_uV(3) / ((5.1/(10+5.1))*1000000.0))
#define get_V_Plus_1() (adc_get_uV(0) / ((5.1/(10+5.1))*1000000.0))
#define get_V_Plus_2() (adc_get_uV(2) / ((5.1/(10+5.1))*1000000.0))

#endif /* _ANALOG_CONVERSION_H_ */