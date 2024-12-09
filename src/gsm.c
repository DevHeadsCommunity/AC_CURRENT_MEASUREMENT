#include "gsm.h"
#include "timer4.h"

char value33[10] = {0};
char jsonPayload[350];
char gsm_uart_data;
char gsm_uart_data2[300] = {0};
int data_position = 0;
int time_push = 0;
char push_data = 0;
int readFlag = 0;
char *buff_()
{
	readFlag = 1;
	// delay_ms(1);
	return gsm_uart_data2;
}

//
// void sendCommand(char *cmd, int Mdelay){
//	gsm_printf(cmd);
//
//}

void gsm_send_to_server(int power_consumed, int energy_used,
						int ac_voltage, int current)
{
//USART2->CR1 &= ~(1 << 5);
	memset(jsonPayload, '\0', strlen(jsonPayload));
	memset(value33, '\0', strlen(value33));
	sprintf(jsonPayload,
			"{\"power\": %d, \"energy\": %d, \"ac_voltage\": %d, \"current\": %d}",
			power_consumed, energy_used, ac_voltage, current);
	// Send the HTTP POST request with the JSON payload
	gsm_printf("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r\n"); // Set GPRS connection type
	delay_ms(3000);
	// uart_printf(jsonPayload);
	gsm_printf("AT+SAPBR=3,1,\"APN\",\" APN \"\r\n"); // Set APN
	delay_ms(3000);
	gsm_printf("AT+SAPBR=1,1\r\n"); // Set APN
	delay_ms(3000);
	gsm_printf("AT+HTTPINIT\r\n");
	delay_ms(3000);
	gsm_printf("AT+HTTPPARA=\"CID\",1\r\n");
	delay_ms(3000);
	gsm_printf("AT+HTTPPARA=\"URL\",\"http://webhook.site/1b0068a8-df8e-4cc8-9c73-7aa638528cae\"\r\n");
	delay_ms(3000);
	gsm_printf("AT+HTTPPARA=\"CONTENT\",\"application/json\"\r\n");
	delay_ms(3000);
	gsm_printf("AT+HTTPDATA=");
	gsm_printnn(strlen(jsonPayload));
	gsm_printf(",10000\r\n");
	delay_ms(2000);
	gsm_printf(jsonPayload);
	delay_ms(3000);
	USART2->CR1 |= 1 << 5;
	gsm_printf("AT+HTTPACTION=1\r\n");
	delay_ms(20000); // Wait for response
	//	gsm_printf("AT+HTTPREAD\r\n");
	// delay_ms(5000); // Wait for response
    //
	// Terminate HTTP session

	gsm_printf("AT+HTTPTERM\r\n");
	delay_ms(5000);

	gsm_printf("AT+SAPBR=0,1\r\n");
	delay_ms(3000);
	gsm_printf("AT+CFUN=1,1\r\n");
	delay_ms(3000);
	//USART2->CR1 &= ~(1 << 5);
}
	void gsm_init()
	{

		RCC->APB2ENR |= 1 << 2;
		RCC->APB2ENR |= 1 << 0;
		RCC->APB2ENR |= 1 << 14;
		GPIOA->CRH &= ~(0x0F << 4); // clearing tx pin to make all zeros
		GPIOA->CRH |= (0x0B << 4);	// setting the Tx pin to output, and alternate function push pull 1011
		USART1->BRR = 0x1D4C;		// 0x271;//0x1D4C; // setting the baudrate to 9600
		USART1->CR1 |= 1 << 5;
		USART1->CR1 |= (3 << 2);  // enabling tx and rx
		USART1->CR1 |= (1 << 13); // enabling usart1
		NVIC_EnableIRQ(USART1_IRQn);
	}

	void USART1_IRQHandler(void)
	{

		if (USART1->SR & 0x20)
		{
			if (readFlag == 1)
			{
				data_position = strlen(gsm_uart_data2);
				for (int i = 0; i < data_position; i++)
				{
					gsm_uart_data2[i] = 0;
				}
				data_position = 0;
			}
			readFlag = 0;
			gsm_uart_data2[data_position] = (char)USART1->DR;
			data_position++;
		}
		debug.printf(buff_());
	}

	void gsm_print(uint8_t data)
	{
		USART1->DR = data;

		while (!(USART1->SR & 0x40))
			;
	}

	void gsm_printf(char *str)
	{

		while (*str)
		{
			gsm_print(*str);
			str++;
			for (long i = 0; i < 100; i++)
				;
		}
	}
	
	void gsm_printnn(int numb) {
	sprintf(value33, "%d", numb);
	gsm_printf(value33);
}
	// Construct the JSON payload
