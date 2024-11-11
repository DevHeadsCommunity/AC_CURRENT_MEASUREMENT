#ifndef INC_TIMER2_H_
#define INC_TIMER2_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f1xx.h"

typedef struct 
{
   void (*init)(void);
}TIMER2_typedef;
extern TIMER2_typedef timer2;
void timer2_Init(void);


#endif /* INC_TIMER2_H_ */