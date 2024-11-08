// #include "FreeRTOS.h"
// #include "gpio_driver.h"
// #include "i2c_driver.h"
// #include "i2c_lcd_driver.h"
// #include "max6675_driver.h"
// #include "spi_driver.h"
#include <stdio.h>
#include <stdlib.h>

#include "stm32f1xx.h"
// #include "task.h"
#include "utils.h"
#include "timer4.h"
#include "uart.h"
#include "adc.h"
#include "timer2.h"
#include "custom_init.h"
int counter = 0;
int value = 0;
readValue_t  mains, ac_current;
int main()
{
	sysclock_init();
	systick_init();
	timer4_Init();
	delay_ms(10);
	uart_init();
	delay_ms(10);
	adc_Init();
	timer2_Init();

	
	TIM2->CR1 |= 1 << 0;
	while (1)
	{
         uart_printf("ENERGY(WH) = ");
		 uart_printn(mains_energy);
		 uart_printf("\r\n");
		GPIOA->ODR ^= (1 << 11);
		delay_ms(1000);
	}
}

void TIM2_IRQHandler(void) {
	//timerTick++;
	value1++;
	/* PA0 = ADCVALUE[1];
	 * PA1 = ADCVALUE[2];
	 * PA4 = ADCVALUE[3];
	 * PA5 = ADCVALUE[0];
	 *
	 * 
	adc1 = adcValue[1] + adc1; // pa0
	adc2 = adcValue[3] + adc2;

	adc3 = adcValue[2] + adc3;

	adc4 = adcValue[3] + adc4;
	*/
	//
	//

	if (mains.temp = adcValue[2], mains.temp > mains.max) { // initially adcValue[2]
		mains.max = mains.temp;
	}
	if (ac_current.temp = adcValue[0], ac_current.temp > ac_current.max) { // initially adcValue[2]
		ac_current.max = ac_current.temp;
	}

	// triggers every 0.02sec
	if (value1 > 400) {
		value1 = 0;
		mains.max = mains.max * (6.6 / 4095);
		ac_current.max = ac_current.max * (6.6 / 4095);

		mains.max = mains.max - 3.3;
		ac_current.max = ac_current.max - 3.3;

		mains.max = mains.max * 127.73;
		ac_current.max = ac_current.max * 10.0;

		
		mains.value += (mains.max * 0.707106);
		ac_current.value += (ac_current.max * 0.707106) - 0.2;

		mains.temp = 0;
		ac_current.temp = 0;
		mains.max = 0;
		ac_current.max = 0;
		timer2_count++;
	}

	// calculate energy every seconds
	if (timer2_count > 50) {

		mains.final_value = mains.value / timer2_count;

		if (mains.final_value < MIN_VOLTAGE_THRESHOLD) { // MIN_VOLTAGE_THRESHOLD = 65
			mains.final_value = 0;
		}

		ac_current.final_value = ac_current.value / timer2_count;

		if (mains.final_value > MAX_VOLTAGE_THRESHOLD) { // MAX_VOLTAGE_THRESHOLD = 180
			mains_power = mains.final_value * ac_current.final_value;
		} else {
			mains_power = 0;
		}

		mains_energy += mains_power / SEC_PER_HOUR; // SEC_PER_HOUR = 3600

		mains.value = 0;
		ac_current.value = 0;
		//GPIOC->ODR ^= (1 << 13);
		timer2_count = 0;
	}

	TIM2->SR &= ~(1 << 0);	// ack the interrupt
}
