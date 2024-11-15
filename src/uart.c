#include "uart.h"
volatile char temp_uart_data[20] = {0};
uint8_t debug_flag = 0;
int data_debug_position =0;
//char value[10] ={0};

UART_typedef debug = {
	.init = uart_init,
	.print = uart_print,
	.printf = uart_printf,
	.printn = uart_printn
};
void uart_init(void) {
   /*  RCC->APB2ENR |= (1 << 0);
	AFIO->MAPR |= (1 << 2); // remap uart to pb6 for tx pb7 for rx
	RCC->APB2ENR |= (1 << 14);  //  enable usart1 clock
	RCC->APB2ENR |= (1 << 3);  // enable port A since TX = PA9 and RX = PA10
	

	GPIOB->CRL &= ~(0x0F << 24);   //clearing tx pin to make all zeros
	GPIOB->CRL |= (0x0B << 24); //setting the Tx pin to output, and alternate function push pull 1011
	///GPIOC ->CRH &= ~(0x0F << 20);
	//GPIOC ->CRH |= (3 << 20);
	// setting the rx pin is not necessary, because at reset the pins are set as input  ** TAKE NOTE*
	//GPIOB ->CRL &= ~(0x0F << 28);   //clearing rx pin to make all zeros
	//GPIOB ->CRL |= (1 << 30);    //setting the rx pin to input

	//setting the baudrate in BRR register
	USART1->BRR = 0x1D4C;	//0x271;//0x1D4C; // setting the baudrate to 9600

	// enabling interrupt on uasart1 for tx and rx
	//USART2 -> CR1 |= (0xA0 <<0);
	//USART1->CR1 |= 1 << 5;
	USART1->CR1 |= USART_CR1_RXNEIE;

	// enabling the tx, rx and uart enable7
	USART1->CR1 |= (3 << 2); // enabling tx and rx
	USART1->CR1 |= (1 << 13);   // enabling usart1
	NVIC_EnableIRQ(USART1_IRQn);*/

 RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;   // Enable GPIOB clock
  RCC->APB1ENR |= RCC_APB1ENR_USART3EN; // Enable USART3 clock

  // Configure PB10 (TX) as Alternate Function Push-Pull, max speed 50 MHz
  GPIOB->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10);
  GPIOB->CRH |= (GPIO_CRH_MODE10_1 | GPIO_CRH_CNF10_1); // PB10: AF push-pull

  // Configure PB11 (RX) as Input Floating
  GPIOB->CRH &= ~(GPIO_CRH_MODE11 | GPIO_CRH_CNF11);
  GPIOB->CRH |= (GPIO_CRH_CNF11_0); // PB11: Input floating

  // Configure USART3: 9600 baud, 8 data bits, 1 stop bit, no parity
  USART3->BRR =
      (234 << 4) | 6;          // Set baud rate to 9600, assuming PCLK1 = 36 MHz
  USART3->CR1 &= ~USART_CR1_M; // 8 data bits
  USART3->CR2 &= ~USART_CR2_STOP; // 1 stop bit
  USART3->CR1 &= ~USART_CR1_PCE;  // No parity

  // Enable USART3, Transmitter, and Receiver

  USART3->CR1 |= USART_CR1_TE; // Enable Transmitter
  USART3->CR1 |= USART_CR1_RE; // Enable Receiver

  // Enable USART3 Receive interrupt (RXNEIE)
  USART3->CR1 |= USART_CR1_RXNEIE;
  USART3->CR1 |= USART_CR1_UE; // Enable USART3
  // Enable USART3 interrupt in NVIC
  NVIC_EnableIRQ(USART3_IRQn);
  NVIC_SetPriority(USART3_IRQn, 1); // Set priority (optional)

}

/////

void USART3_IRQHandler(void) {

	if ( USART3->SR & 0x20) {


//		if (debug_flag == 1) {
//					data_debug_position = strlen(temp_uart_data);
//					for (int i = 0; i < data_debug_position; i++) {
//						temp_uart_data[i] = 0;
//						//delay_ms(1);
//					}
//					data_debug_position = 0;
//				}
				//debug_flag = 0;
				//temp_uart_data[data_debug_position] = (char) USART1->DR;
				//data_debug_position++;
debug_flag = USART3->DR;

		//GPIOA->ODR |= (1 << 11);
	}
	if (USART3->SR & 0x80) {

	}

}

void uart_print(char data) {
	USART3->DR = data;
    
	while (!(USART3->SR & 0x40))
		;
}

void uart_printf(char *str) {

	while (*str) {
		uart_print(*str);
		str++;
		//delay_ms(100);
	}

}

void uart_printn(float x) {
//char value1[10];
//	sprintf(value1, "%d", d_numb);
//	//lcd_clear();
//	uart_print('\0');
//	uart_printf((char*) value1);

	uint8_t a = 0;
	uint8_t b = 0;
	uint8_t c = 0;
	uint8_t d = 0;
	uint16_t e, g, h, t = 0;

	t = x;
	a = (t / 1000);
	b = ((t / 100) % 10);
	c = ((t / 10) % 10);
	d = (t % 10);
	x = x - t;
	e = x * 100;
	g = e / 10;
	h = e % 10;

	if (a == 0) {

	} else {
		uart_print(a + 0x30);
	}
	if ((b == 0) && (a == 0)) {

	} else {
		uart_print(b + 0x30);
	}

	if ((b == 0) && (a == 0) && (c == 0)) {

	} else {
		uart_print(c + 0x30);
	}
	uart_print(d + 0x30);
	delay_ms(1);
	uart_print('.');
	delay_ms(5);
	uart_print(g + 0x30);
	delay_ms(5);
	uart_print(h + 0x30);

}
