#include "osKernel.h"
#include "STM32F4_RTOS_BSP.h"

#define QUANTA 1

uint32_t count0, count1, count2;

void Task0(void)
{
	while(1)
	{
		count0++;
		osThreadYield();
	}
}

void Task1(void)
{
	while(1)
	{
		count1++;
	}
}

void Task2(void)
{
	while(1)
	{
		count2++;
	}
}

int main(void)
{
	HAL_Init();
	Probe_Init();
	TIM4_Init_Start();
	osKernelInit();
	osKernelAddThread(&Task0, &Task1, &Task2);
	osKernelLaunch(QUANTA);
}

void TIM4_IRQHandler(void)
{
  Probe_CH0();
  HAL_TIM_IRQHandler(&htim4);

}

