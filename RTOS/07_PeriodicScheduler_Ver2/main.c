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

#define GREEN			(1U<<12)
#define ORANGE 			(1U<<13)
#define RED			(1U<<14)
#define BLUE			(1U<<15)

#define GREEN_BIT		(1U<<24)
#define ORANGE_BIT 		(1U<<26)
#define RED_BIT			(1U<<28)
#define BLUE_BIT		(1U<<30)

#define GPIOD_CLOCK_BIT (1<<3)

void LED_Init()
{
	RCC->AHB1ENR |= GPIOD_CLOCK_BIT; 
	
	GPIOD->MODER |= (GREEN_BIT | ORANGE_BIT | RED_BIT | BLUE_BIT);	//set the port D MODER register to output on the LED bits
}

void Task3(void)
{
	GPIOD->ODR ^= ORANGE;
}

int main(void)
{
	HAL_Init();
	Probe_Init();
	LED_Init();
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

