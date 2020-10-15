#include "IO.h"
#include "stm32f4xx.h"                  // Device header

void GPIO_Init(void)
{
	RCC->AHB1ENR |= (GPIOA_CLOCK_BIT | GPIOD_CLOCK_BIT); //enable clock on port A (for button) and D (for leds)
	
	GPIOA->MODER |= BTN_BIT; //set the port A MODER register to input on the button bit
	GPIOD->MODER |= (GREEN_BIT | ORANGE_BIT | RED_BIT | BLUE_BIT);	//set the port D MODER register to output on the LED bits
}

void LED_On(uint32_t leds)
{
	GPIOD->ODR |= leds;
}

void LED_Off(uint32_t leds)
{
	GPIOD->ODR &= ~leds;
}
