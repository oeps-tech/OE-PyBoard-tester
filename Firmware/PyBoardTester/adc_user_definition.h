#ifndef ADC_USER_DEFINITION_H
#define ADC_USER_DEFINITION_H


// Change the constants below before compiling
// Each device will have it's own calibration values

#define ADC_USER_NUMBER_OF_ADCs	4			// Number of analog channels being used

// These were measured on PA1

#define ADC_USER_CAL_LOW_SUM16  38686L		// Sum of 16 measurements
#define ADC_USER_CAL_LOW_UV     1112000L	// Voltage (uV) used at ADC pin for the above 16 measurements

#define ADC_USER_CAL_HIGH_SUM16 54931L		// Sum of 16 measurements
#define ADC_USER_CAL_HIGH_UV    1621000L	// Voltage (uV) used at ADC pin for the above 16 measurements


#endif /* ADC_USER_DEFINITION_H */