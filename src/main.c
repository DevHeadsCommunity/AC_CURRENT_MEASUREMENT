// #include "FreeRTOS.h"

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
#include "eeprom.h"
#include "i2c.h"
int counter = 0;
int value = 0;

int main()
{
	sysclock_init();
	systick_init();
	delay.init();
	delay.ms(10);
	debug.init();
	delay.ms(10);
	adc_Init();
	custom_init();
	i2c_init();
	timer2.init();
	delay.ms(9000);
	debug.init();
	delay.ms(1);
	debug.printf("location 0 = ");
	delay_ms(1);
	debug.printn(eeprom_read(0));
	debug.printf("\r\n");
	while (1)
	{

		if (value1 > 400)
		{
			TIM2->CR1 &= ~(1 << 0);
			value1 = 0;
			// TIM2->CR1 &= ~(1 << 0);
			mains.max = mains.max * (6.6 / 4095);
			ac_current.max = ac_current.max * (6.6 / 4095);

			mains.max = mains.max - 3.281;
			ac_current.max = ac_current.max - 3.291;

			mains.max = mains.max * 249.73;
			ac_current.max = ac_current.max * 8.0;

			mains.value += (mains.max * 0.707106);
			ac_current.value += (ac_current.max * 0.707106) - 0.2;

			mains.temp = 0;
			ac_current.temp = 0;
			mains.max = 0;
			ac_current.max = 0;
			counter_check = 0;
			timer2_count++;
			TIM2->CR1 |= 1 << 0;
		}

		if (timer2_count > 50)
		{
			counter_check = 1;
			mains.final_value = mains.value / timer2_count;

			if (mains.final_value < MIN_VOLTAGE_THRESHOLD)
			{ // MIN_VOLTAGE_THRESHOLD = 65
				mains.final_value = 0;
			}

			ac_current.final_value = ac_current.value / timer2_count;

			if (mains.final_value > MAX_VOLTAGE_THRESHOLD)
			{ // MAX_VOLTAGE_THRESHOLD = 180
				mains_power = mains.final_value * ac_current.final_value;
			}
			else
			{
				mains_power = 0;
			}

			mains_energy += mains_power / SEC_PER_HOUR; // SEC_PER_HOUR = 3600

			mains.value = 0;
			ac_current.value = 0;

			timer2_count = 0;
			debug.printf("MAINS = ");
			delay.ms(1);
			debug.printn(mains.final_value);
			delay.ms(1);
			debug.printf("  ");
			delay.ms(1);
			debug.printf("AC_CURRENT = ");
			delay.ms(1);
			debug.printn(ac_current.final_value);
			delay.ms(1);
			debug.printf("  ");
			delay.ms(1);
			debug.printf("ENERGY = ");
			delay.ms(1);
			debug.printn(mains_energy);
			delay.ms(1);

			debug.printf("\r\n");
			GPIOA->ODR ^= (1 << 11);
		}

		// GPIOA->ODR ^= (1 << 11);
		// delay.ms(1000);
	}
}

void TIM2_IRQHandler(void)
{
	// timerTick++;

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
	value1++;
	if (mains.temp = adcValue[2], mains.temp > mains.max)
	{ // initially adcValue[2]
		mains.max = mains.temp;
	}
	if (ac_current.temp = adcValue[3], ac_current.temp > ac_current.max)
	{ // initially adcValue[2]
		ac_current.max = ac_current.temp;
	}

	TIM2->SR &= ~(1 << 0); // ack the interrupt
}
