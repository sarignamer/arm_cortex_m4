#include "stm32f4xx.h"                  // Device header

/*----------LEDS-----------*/
#define GREEN		(1U << 12)
#define ORANGE 	(1U << 13)
#define RED			(1U << 14)
#define BLUE		(1U << 15)

//output bits
#define GREEN_BIT				(1U << 24)
#define ORANGE_BIT 			(1U << 26)
#define RED_BIT					(1U << 28)
#define BLUE_BIT				(1U << 30)

/*----------Ports Clocks-----------*/
#define GPIOD_CLOCK_BIT (1U << 0)


int main()
{
	RCC->AHB1ENR |= GPIOD_CLOCK_BIT; //enable clock on port D (for leds)
	GPIOD->MODER |= (GREEN_BIT | ORANGE_BIT | RED_BIT | BLUE_BIT);	//set the port D MODER register to output on the LED bits
}

void Timer1_oneshot(int msdelay)
{
	