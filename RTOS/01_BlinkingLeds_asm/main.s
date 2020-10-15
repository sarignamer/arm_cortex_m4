RCC_BASE	EQU	0x40023800	; RCC start adress
RCC_AHB1ENR	EQU	0x40023830	; RCC_BASE + 0x30 which is the memroy offset for AHB1ENR
GPIOD_BASE	EQU	0x40020C00
GPIOD_MODER	EQU	GPIOD_BASE
GPIOD_ODR	EQU 0x40020C14	; GPIOD_BASE + 0x14 which is output data register for port D
	
GPIODEN		EQU	1 << 3

LED_GREEN	EQU	1 << 12
LED_ORANGE	EQU	1 << 13
LED_RED		EQU	1 << 14
LED_BLUE	EQU	1 << 15

MODER12_OUT	EQU	1 << 24	; Set pin 12 as an output
MODER13_OUT	EQU	1 << 26
MODER14_OUT	EQU	1 << 28
MODER15_OUT	EQU	1 << 30
	
DELAY		EQU	0x000F

ONESEC		EQU	5333333
HSEC		EQU 266667	; half second
FSEC		EQU 106667	; fifth of a second
	
	
			AREA |.text|,CODE,READONLY,ALIGN=2
			THUMB
			EXPORT __main
				
__main
	BL	GPIOD_Init
	
GPIOD_Init
	; Enable Clock access on port D
	LDR	R0,=RCC_AHB1ENR	; R0 points to peripheral clock register
	LDR	R1,[R0]			; Loads the content of R0 (peripheral clock register) into R1
	ORR R1,GPIODEN		; RCC_AHB1ENR ORR 1 << 3, store the results in R1
	STR R1,[R0]			; Store the content of R1 into R0 (RCC_AHB1ENR)
	
	; Set the pins as output pins on port D by changing the mode register
	LDR	R0,=GPIOD_MODER											; R0 points to PORT D configuration register
	LDR	R1,=(MODER12_OUT|MODER13_OUT|MODER14_OUT|MODER15_OUT)	; R1 points to pins 12,13,14,15 on the configuration register
	STR	R1,[R0]													; Store pins 12,13,14,15 into MODER
	MOV R1,#0													; Clear R1				
	LDR R2,=GPIOD_ODR											; GPIOD output data register
	
Blink
	; Main blinking sequance
	MOVW	R1,#LED_GREEN		; Select the green led
	STR		R1,[R2]				; Store the selected led on the output data register
	LDR 	R3,=ONESEC			; Set delay amount
	BL		Delay
	MOVW 	R1,#LED_ORANGE		; Select the green led
	STR 	R1,[R2]				; Store the selected led on the output data register
	LDR 	R3,=HSEC			; Set delay amount
	BL		Delay
	MOVW 	R1,#LED_RED			; Select the green led
	STR 	R1,[R2]				; Store the selected led on the output data register
	LDR 	R3,=ONESEC			; Set delay amount
	BL		Delay
	MOVW 	R1,#LED_BLUE		; Select the green led
	STR 	R1,[R2]				; Store the selected led on the output data register
	LDR 	R3,=FSEC			; Set delay amount
	BL		Delay
	B		Blink
	
Delay
	; Delay function
	SUBS	R3,R3,#1	; Substract 1 from R3 and store it in R3
	BNE		Delay
	BX		LR
	ALIGN
	END