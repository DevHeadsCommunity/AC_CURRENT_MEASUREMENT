#include "eeprom.h"
#include "i2c.h"
char EEprom_data = 0;
uint8_t eeprom_temp = 0;
uint8_t eeprom_buff[5] = {0};


void eeprom_write(char address, char eeprom_data)
{
            i2c_start();
			delay.ms(5);
			i2c_addr(EEPROM_WRITE);
			delay.ms(5);
			i2c_mem_addr(address);
			delay.ms(5);
			i2c_write_data(eeprom_data);
			i2c_stop();
}


 uint8_t eeprom_read(char address)
{
    i2c_start();
    delay.ms(5);
    i2c_addr(EEPROM_WRITE);
    delay.ms(5);
    i2c_mem_addr(address);
    i2c_start();
    delay.ms(10);
    i2c_addr(EEPROM_READ);
    delay.ms(10);
    EEprom_data = I2C1->DR;
    i2c_stop();
    return EEprom_data;
}