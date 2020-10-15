#include "osKernel.h"
#include "STM32F4_RTOS_BSP.h"

#define QUANTA 1

void Task0(void)
{
	while(1)
	{
		
	}
}

void Task1(void)
{
	while(1)
	{
		
	}
}

void Task2(void)
{
	while(1)
	{
		
	}
}

int main(void)
{
	HAL_Init();
	Probe_Init();
	osKernelInit();
	osKernelAddThread(&Task0, &Task1, &Task2);
	osKernelLaunch(QUANTA);
}
