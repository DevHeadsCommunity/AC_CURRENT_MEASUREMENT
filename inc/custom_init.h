#ifndef INC_CUSTOM_INIT_H_
#define INC_CUSTOM_INIT_H_

#include <stdint.h>
#include <stdio.h>
#include "stm32f1xx.h"

#define ONBOARDLEDON GPIOA->ODR |= (1 << 11)
#define ONBOARDLEDOFF GPIOA->ODR &= ~(1 << 11)
#define BUZZERON GPIOB->ODR |= (1 << 3)
#define BUZZEROFF GPIOB->ODR &= ~(1 << 3)
#define MIN_VOLTAGE_THRESHOLD  65
#define MAX_VOLTAGE_THRESHOLD 180
#define SEC_PER_HOUR  3600
extern uint16_t value1;
extern uint8_t timer2_count;
extern long adc1, adc2, adc3, adc4, adc5, adc6;
extern float mains_power;
extern float mains_energy;

void custom_init(void);
typedef struct {
	uint16_t temp;
	float max;
	float value;
	float final_value;
} readValue_t;

#endif /* INC_CUSTOM_INIT_H_ */