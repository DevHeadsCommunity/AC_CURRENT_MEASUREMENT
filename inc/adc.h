#ifndef __ADC_H
#define __ADC_H
#include <stdint.h>
#include "stm32f1xx.h"
void adc_Init(void);
extern uint16_t adcValue[4];
extern uint8_t lcdChange;
extern uint16_t lcdCount;
extern uint8_t lcdCheck;
extern float  battery;
#endif /* INC_ADC_H_ */