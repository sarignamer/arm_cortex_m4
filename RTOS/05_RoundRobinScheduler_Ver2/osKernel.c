#include "osKernel.h"

//--------------DEFINES---------------
#define INTERUPT_CTRL (*((volatile uint32_t*)0xE000ED04)) //The adress if the interput controller register

#define NUM_OF_THREADS	3
#define STACKSIZE				100

#define BUS_FREQ				16000000


//--------------Prototypes---------------
void osSchedulerLaunch(void);

typedef struct tcb
{
	int32_t* stackPt;
	struct tcb* nextPtr;
} tcbType;

//--------------Globals---------------
tcbType tcbs[NUM_OF_THREADS];
tcbType* currentPt;

int32_t TCB_STACK[NUM_OF_THREADS][STACKSIZE];

uint32_t MILLIS_PRESCALER;



void osKernelStackInit(int i, void(*task)(void))
{
	tcbs[i].stackPt = &TCB_STACK[i][STACKSIZE - 16]; //we substract 16 to leave room for registers R0-R15
	
	TCB_STACK[i][STACKSIZE - 1] = 0x01000000; //[STACKSIZE - 1] is the xPSR register
																						//Explicit initialize the xPSR register to be in thumb mode.
																						//Even if the proccessor can only run in thumb mode, still need to do it.
	
	TCB_STACK[i][STACKSIZE - 2] = (int32_t)(task); //[STACKSIZE - 2] is the PC register;
}

uint8_t osKernelAddThread(void(*task0)(void),
													void(*task1)(void),
													void(*task2)(void))
{
	__disable_irq(); //disable interputs
	
	tcbs[0].nextPtr = &tcbs[1];
	tcbs[1].nextPtr = &tcbs[2];
	tcbs[2].nextPtr = &tcbs[0];
	
	osKernelStackInit(0, task0);
	osKernelStackInit(1, task1);
	osKernelStackInit(2, task2);
	
	currentPt = &tcbs[0];
	
	__enable_irq(); //enable interputs
	
	return 1;
}

void osKernelInit(void)
{
	__disable_irq();
	
	MILLIS_PRESCALER = BUS_FREQ / 1000;
}

void osKernelLaunch(uint32_t quantaInMS)
{
	SysTick->CTRL = 0;	//disable the systick
	SysTick->VAL = 0;
	NVIC_SetPriority(SysTick_IRQn, 7); //set SysTick to the lowest priority
	SysTick->LOAD = quantaInMS * MILLIS_PRESCALER - 1; //Set the countdown for the tick
	SysTick->CTRL = 0x00000007; //We put the value 0x7 to:
															//Enable the counter
															//Cause excpetion request on countdown
															//To use the proccessor clock
	osSchedulerLaunch();
}

void osThreadYield(void)
{
	INTERUPT_CTRL = 0x04000000; //trigger SysTick
}
