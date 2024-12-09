#ifndef INC_GSM_H_
#define INC_GSM_H_
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "stm32f1xx.h"
#include "uart.h"
void gsm_send_to_server(int power_consumed, int energy_used,
		int ac_voltage, int current);
void gsm_init();
void gsm_print(uint8_t data);
void gsm_printf(char *str);
void gsm_printn(float x);
void gsm_printnn(int numb);
void USART2_IRQHandler(void);
extern char gsm_uart_data;
extern char gsm_uart_data2[300];
extern int readFlag;
extern int data_position;
extern int time_push;
extern char push_data;
#endif /* INC_GSM_H_ */