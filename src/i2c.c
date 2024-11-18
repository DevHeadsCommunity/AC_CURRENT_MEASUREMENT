#include "i2c.h"
char temp_value=0;
void i2c_init(void) {
	RCC->APB2ENR |= 1 << 3; // enable portb clock
	RCC->APB2ENR |= 1 << 0; // enable portb clock
	RCC->APB1ENR |= 1 << 21;  // enable i2c clock

	I2C1->CR2 |= 36;
	I2C1->CCR |= 180;  // setting the value to
	I2C1->TRISE |= 37;
	I2C1->CR1 |= 1 << 10; // enable ack
	// 7 bit addressing mode is enabled by default
	GPIOB->CRL &= ~(0x0F << 24); // SCL LINE SET AS OUTPUT, OPEN DRAIN PB6
	GPIOB->CRL |= (0x0F << 24);

	GPIOB->CRL &= ~(0x0F << 28); // SDA LINE SET AS OUTPUT, OPEN DRAIN PB7
	GPIOB->CRL |= (0x0F << 28);
     delay_ms(10);
	I2C1->CR1 |= (1 << 0); // enable peripherial

}

void i2c_start(void)
{

	I2C1->CR1 |= (1 << 8);

		while(!(I2C1 -> SR1 & I2C_SR1_SB));


}


void i2c_addr(char addr)
{

	I2C1->DR = addr;
	while(!(I2C1->SR1 & I2C_SR1_ADDR));
	temp_value= I2C1->SR2;

}

void i2c_mem_addr(char mem_addr)
{

	I2C1->DR = mem_addr;
	while(!(I2C1->SR1 & I2C_SR1_TXE));


}

void i2c_write_data(int data)
{
	    I2C1->DR = data;
		while(!(I2C1->SR1 & I2C_SR1_TXE));
}


void i2c_stop(void)
{
	I2C1->CR1 |= (1<<9);

}

void i2c_read(void)
{

}
