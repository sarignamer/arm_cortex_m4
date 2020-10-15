#include "Delay.h"

void Delay(unsigned int time)
{
	int volatile delay;
	delay = 0;
	while((delay++) < time);
}