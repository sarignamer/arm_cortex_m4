#ifndef __IO_H__
#define __IO_H__

#include <stdint.h>

/*----------LEDS-----------*/
#define GREEN		(1U << 12)
#define ORANGE 	(1U << 13)
#define RED			(1U << 14)
#define BLUE		(1U << 15)

#define GREEN_BIT				(1U << 24)
#define ORANGE_BIT 			(1U << 26)
#define RED_BIT					(1U << 28)
#define BLUE_BIT				(1U << 30)

/*----------Push Button-----------*/
#define BTN 		(1U << 0)
#define BTN_BIT 				(0U)

/*----------Ports Clocks-----------*/
#define GPIOA_CLOCK_BIT (1U << 0)
#define GPIOD_CLOCK_BIT (1U << 3)

void GPIO_Init(void);
void LED_On(uint32_t leds);
void LED_Off(uint32_t leds);

#endif //__IO_H__