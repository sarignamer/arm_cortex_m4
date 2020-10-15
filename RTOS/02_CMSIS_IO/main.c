#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
#include "IO.h"

void GPIO_Init(void);

int main(void)
{
	GPIO_Init();
	
	while (1)
	{
		if (GPIOA->IDR & BTN)
		{
			LED_On(GREEN | ORANGE | RED | BLUE);
			Delay(1000000);
			LED_Off(GREEN | ORANGE | RED | BLUE);
		}
	}
}