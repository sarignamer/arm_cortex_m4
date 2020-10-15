#ifndef __OS_KERNERL_H__
#define __OS_KERNERL_H__

#include "stm32f4xx.h"                  // Device header
#include <stdint.h>

void osKernelLaunch(uint32_t quantaInMS);

void osKernelInit(void);

uint8_t osKernelAddThread(void(*task0)(void),
													void(*task1)(void),
													void(*task2)(void));
													
void osThreadYield(void);
													
void osSemahoreInit(int32_t* semaphore, int32_t value);

void osSignelSet(int32_t* semaphore);

void osSignalWait(int32_t* semaphore);

#endif //__OS_KERNERL_H__
	
