# ARM_Cortex_M4

Hardware used: STM32F411VET6U discovery board

Software: Keil5

## 01. BlinkingLeds_asm

A simple project written in assembly to make the leds on the board blink

## 02. CMSIS_IO

Basic IO using the CMSIS API

## 03. SVC_Exceptions

A porgram to show the use of Supervisor Call Exception, known as SVC.

SVC works in a privilage mode and it shows how write functions that will force the program to switch to privilage mode.

## 04. RoundRobinScheduler_Ver1

Very basic OS with Round Robin Scheduler.

It handles exactly 3 threads in a static mode, no threads can be added and no threads can be removed.

It uses the Cortex-M API SysTick to measure Quanta time. Each time the SysTick interputs occurs, the kernel perform a context switch for the threads, and move to the next thread.

## 05. RoundRobinScheduler_Ver2

Same as RoundRobinScheduler_Ver1, except, it is now with **Cooperative** Round Robin scheduler. It means that a thread can tell the os that it is finished even if quanta time has not yet passed and the scheduler can perform a context switch to the next thread.

## 06. PeriodicScheduler_Ver1

Based on RoundRobinScheduler_Ver2, but this time with periodic threads that works accoriding to timers. Each time a selcted timer reaches it's period it sends an iterrupt which can be used as the periodic thread.

Also added is a BSP package that allows control of the timers.

## 07. PeriodicScheduler_Ver2

Based on RoundRobinScheduler_Ver2, but this time with periodic threads that works accoriding to SysTick, every Xms Peroid (defined in Kernel.h), the program will perform a task (thread) and then will continue to as regular.

## 08. SpinLock_Sempahore

Based on RoundRobinScheduler_Ver2.

Added basic semphore capabilities, so now we have a basic OS, which can be expanded upon.

## 09_CMSIS_ThreadCreation

CMSIS-RTOS RTX Thread creation example.

How to use the RTOS that is supplied with every cortex chip.