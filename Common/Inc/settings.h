#ifndef SETTINGS_H
#define SETTINGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

//FIR filter order
#define FILTER_ORDER (uint32_t)45

//FIR filter coefficients number
#define NUM_OF_COEF (uint32_t)FILTER_ORDER + 1

//splitter, from 0 to SPLITTER core 0 (M7) is calculating, from SPLITTER to NUM_OF_COEF core 1 (M4) is calculating
#define SPLITTER (uint32_t)35

#define ADC_BUF_START_ADDRESS (uint32_t)0x38000000
#define ADC_BUF_END_ADDRESS (uint32_t)(ADC_BUF_START_ADDRESS + (NUM_OF_COEF-1)*sizeof(uint32_t))

#define ADC_DMA_ADDRESS (uint32_t)0x38000400

typedef enum
{
	READY_FOR_OUTPUT,
	CALCULATION,

} FIR_State;

typedef struct
{
	const uint32_t 	splitter,
					coefNum;

	float 		result_c0,
				result_c1;

	FIR_State 	*FIR_state_c0,
				*FIR_state_c1;

	const float * const FIR_coef;


    uint32_t 	*bufferStartPointer,
				*bufferCurrentPointer,
				*bufferEndPointer;

} FIR_Instance;


extern FIR_Instance FIR_filter;

extern const float FIR_coefficients[NUM_OF_COEF];

extern FIR_State 	FIR_state_core0,
					FIR_state_core1;

#ifdef __cplusplus
}
#endif

#endif
