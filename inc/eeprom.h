#ifndef INC_EEPROM_H_
#define INC_EEPROM_H_
#define EEPROM_WRITE 0xA0
#define EEPROM_READ 0xA1
#include <stdint.h>
#include "stm32f1xx.h"
//void eeprom_write(uint8_t address, uint8_t data);
//void eeprom_read(uint8_t lenght);
void eeprom_write(char address,char eeprom_data);
 uint8_t eeprom_read(char address);


extern char EEprom_data;
extern uint8_t eeprom_buff[5];
extern uint8_t eeprom_temp;
#endif /* INC_EEPROM_H_ */
