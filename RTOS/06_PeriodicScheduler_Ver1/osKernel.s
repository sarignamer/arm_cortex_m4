				AREA |.text|, CODE,READONLY,ALIGN=2
				THUMB
				EXTERN currentPt
				EXPORT SysTick_Handler
				EXPORT osSchedulerLaunch

; On Each SysTick_Handler save the current thread and load the next thread:
; --------------------------------------
; 1. save stack to thread (currentPtr->stackPtr)
; 2. switch to the new thread (currentPtr = currentPtr->nextPtr)
; 3. load stack from next thread for switch (SP = currentPtr->stackPtr)

SysTick_Handler				; Invoking the call, auto saves R0, R1, R2, R3, R12, LR, PC, PSR
	CPSID	I				; Disable interupts
	PUSH	{R4-R11} 		; Push registers R4 to R11 unto the stack (saving them)
	LDR		R0,=currentPt	; R0 points to currentPt (R0 = &currentPt)
	LDR		R1,[R0]			; R1 is currentPt (R1 = currentPt)
	STR		SP,[R1]			; Saves the SP to R1 (currentPt->stackPtr = SP)
	LDR		R1,[R1,#4]		; Advance the SP to the next pt in the tcb structure (we #4 for an offset) (R1 = currentPtr->nextPtr)
	STR		R1,[R0]			; R0 now points to the next pt which is also the next thread (currentPtr = R1 = currentPtr->nextPtr)
	LDR		SP,[R1]			; SP = currentPt->stackPtr
	POP		{R4-R11}		; restore R4 to R11 from new stack (the stack of the next thread)
	CPSIE	I				; Enable interputs
	BX		LR		      	; return from subroutine. Automatically restores R0, R1, R2, R3, R12, LR, PC, PSR from new stack (next thread)



osSchedulerLaunch			; We launch the scheduler by setting SP to the value of the first thread
	LDR		R0,=currentPt
	LDR		R2,[R0]			; R2 = currentPt
	LDR		SP,[R2]			; SP = currentPt->stackPt
	POP		{R4-R11}		; restore R4 to R11 from the thread stack
	POP		{R0-R3}
	POP		{R12}
	ADD		SP,SP,#4		; Skip LR
	POP		{LR}
	ADD		SP,SP,#4		; Skip PSR
	CPSIE	I				; Enable interputs
	BX		LR
	
	
	ALIGN
	END