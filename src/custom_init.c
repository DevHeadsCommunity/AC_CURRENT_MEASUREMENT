#include "custom_init.h"


uint8_t timer2_count = 0;
uint16_t value1 = 0;
long adc1, adc2, adc3, adc4, adc5, adc6;
float mains_power = 0.00;
float mains_energy = 0.00;
uint8_t counter_check = 0;
readValue_t mains = {
	.final_value =0,
	.max = 0.0,
	.temp = 0.0,
	.value = 0.0
};

readValue_t ac_current = {
	.final_value =0,
	.max = 0.0,
	.temp = 0.0,
	.value = 0.0
};
void custom_Init(void) {
	RCC->APB2ENR |= 1 << 2;		 // enable porta clock
	RCC->APB2ENR |= 1 << 3;
	GPIOA->CRH &= ~(0x0F << 12); // ON BOARD LED
	GPIOA->CRH |= (0x03 << 12);

	GPIOB->CRL &= ~(0x0F << 12);   // BUZZER
	GPIOB->CRL |= (0x03 << 12);

	GPIOB->CRL &= ~(0x0F << 20);   // RELAY
	GPIOB->CRL |= (0x03 << 20);

	GPIOA->CRL &= ~(0x0F << 28); //  FAN
	GPIOA->CRL |= (0x03 << 28);

	GPIOB->CRL &= ~(0x0F << 0);   //switch
	GPIOB->CRL |= (0x04 << 0);

	AFIO->MAPR |= 2 << 24;
}
