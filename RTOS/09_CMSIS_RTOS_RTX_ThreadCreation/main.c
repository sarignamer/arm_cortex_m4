#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "stm32f4xx.h"                  // Device header

int32_t count1, count2, count3;

void Thread1(void const *argument)
{
	while (1)
	{
		count1++;
	}
}

void Thread2(void const *argument)
{
	while (1)
	{
		count2++;
	}
}

void Thread3(void const *argument)
{
	while (1)
	{
		count3++;
	}
}


osThreadDef(Thread1, osPriorityNormal, 1, 0);
osThreadDef(Thread2, osPriorityNormal, 1, 0);
osThreadDef(Thread3, osPriorityNormal, 1, 0);

int main(void)
{
	osThreadCreate(osThread(Thread1), NULL);
	osThreadCreate(osThread(Thread2), NULL);
	osThreadCreate(osThread(Thread3), NULL);
	
	while(1)
	{
	}
	
}

