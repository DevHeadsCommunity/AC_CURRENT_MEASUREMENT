#ifndef __TIMER4_H
#define __TIMER4_H
#include <stdio.h>
#include <stdint.h>
#include "stm32f1xx.h"


typedef struct {
    void (*ms)(int ms);
    void (*us)(int us);
    void (*init)(void);

}DELAY_typedef;
extern DELAY_typedef delay;

void TIM4_IRQHandler(void);

#endif