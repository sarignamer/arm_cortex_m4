
int __svc(0x00) svc_service_add(int x, int y);
int __svc(0x01) svc_service_sub(int x, int y);
int __svc(0x02) svc_service_mul(int x, int y);
int __svc(0x03) svc_service_div(int x, int y);

int x, y, z;

void SVC_Handler_C(unsigned int* svc_args);

int main(void)
{
	x = 1;
	y = 5;
	z = svc_service_add(x, y);
	
	x = 9;
	y = 2;
	z = svc_service_sub(x, y);
	
	x = 9;
	y = 2;
	z = svc_service_sub(x, y);
	
	x = 3;
	y = 4;
	z = svc_service_mul(x, y);
	
	x = 6;
	y = 2;
	z = svc_service_div(x, y);
}

__asm void SVC_Handler(void)
{
	TST LR,#4 		//Test bit 2 on the link register
	ITE EQ				//If then Else block using equal as the condition
	MRSEQ R0,MSP	//If test is equal to zero, copy the main stack pointer to R0
	MRSNE R0,PSP	//If not equal to zero,  copy the proccess stack pointer to R0
	B __cpp(SVC_Handler_C)
}

void SVC_Handler_C(unsigned int* svc_args)
{
	unsigned int svc_number;
	
	/*
	*	svc_args structure:
	*	R15(PC)			-			svc_args[6]
	*	R14(LR)			-			svc_args[5]
	*	R12					-			svc_args[4]
	*	R3					-			svc_args[3]
	*	R2					-			svc_args[2]
	*	R1					-			svc_args[1]
	*	R0					-			svc_args[0]
	*/
	svc_number = ((char*)svc_args[6])[-2];	//svc_args[6] is the program counter
																					//the [-2] is to get the first byte of the svc instruction
																					//which is basicly which function to use
	
	/*
	*	Arm Architecture Procedure Call Standard (AAPCS)
	*	Designates R0 and R1 parameter passing register, and R0 as the return value register,
	* and since the SVC functions we defined only have 2 arguments, they are stored in
	* R0 and R1.
	*/
	switch (svc_number)
	{
		case 0:
			svc_args[0] = svc_args[0] + svc_args[1];	//R0 = R0 + R1
			break;
		case 1:
			svc_args[0] = svc_args[0] - svc_args[1];	//R0 = R0 + R1
			break;
		case 2:
			svc_args[0] = svc_args[0] * svc_args[1];	//R0 = R0 + R1
			break;
		case 3:
			svc_args[0] = svc_args[0] / svc_args[1];	//R0 = R0 + R1
			break;
		default:
			break;
	}
}
