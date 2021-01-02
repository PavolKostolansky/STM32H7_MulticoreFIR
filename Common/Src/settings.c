#include "settings.h"

//used just for memory allocation for the ADC input, code is using pointer arithmetic
uint32_t adcInputArray[NUM_OF_COEF] __attribute__((section(".non_cacheable_vars"))) = {0};

//FIR filter coeficients - 20Khz cutoff /Taylor Window
const float FIR_coefficients[NUM_OF_COEF] __attribute__((section(".cacheable_vars"))) =
{
	    0.00285205082, 0.003712879494, 0.003137147985,0.0009365120204,-0.002484805416,
	  -0.005954552442,-0.007727126591,-0.006166929379,-0.0007250059862, 0.007280696183,
	    0.01463432238,  0.01722848974,  0.01189486682, -0.00165010395, -0.01967664063,
	   -0.03486047313, -0.03839545324, -0.02320784144,  0.01289481763,  0.06544547528,
	     0.1238083914,   0.1740065217,    0.203016758,    0.203016758,   0.1740065217,
	     0.1238083914,  0.06544547528,  0.01289481763, -0.02320784144, -0.03839545324,
	   -0.03486047313, -0.01967664063, -0.00165010395,  0.01189486682,  0.01722848974,
	    0.01463432238, 0.007280696183,-0.0007250059862,-0.006166929379,-0.007727126591,
	  -0.005954552442,-0.002484805416,0.0009365120204, 0.003137147985, 0.003712879494,
	    0.00285205082
};

//FIR state
FIR_State 	FIR_state_core0 __attribute__((section(".non_cacheable_vars"))) = CALCULATION,
			FIR_state_core1 __attribute__((section(".non_cacheable_vars"))) = CALCULATION;

//FIR structure
FIR_Instance FIR_filter __attribute__((section(".non_cacheable_vars"))) =
{
	SPLITTER,
	NUM_OF_COEF,
	0,
	0,
	&FIR_state_core0,
	&FIR_state_core1,
	FIR_coefficients,
	(uint32_t*)ADC_BUF_START_ADDRESS,
	(uint32_t*)ADC_BUF_START_ADDRESS,
	(uint32_t*)ADC_BUF_END_ADDRESS,
};

