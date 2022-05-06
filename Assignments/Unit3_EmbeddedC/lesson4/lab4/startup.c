
//startup.cabs
//Eng.Omar

#include <stdint.h>
#define STACK_Start_SP 0x20001000

extern int main(void);
void Reset_Handler ();

void Default_Handler()
{
		Reset_Handler ();
}


void NMI_Handler ()__attribute((weak,alias("Default_Handler")));
void H_Fault_Handler ()__attribute((weak,alias("Default_Handler")));
void MM_Fault_Handler ()__attribute((weak,alias("Default_Handler")));
void Bus_Fault_Handler ()__attribute((weak,alias("Default_Handler")));
void Usage_Fault_Handler ()__attribute((weak,alias("Default_Handler")));

extern unsigned int _E_text ;
extern unsigned int _S_DATA ;
extern unsigned int _E_DATA ;
extern unsigned int _S_bss ;
extern unsigned int _E_bss ;
extern unsigned int _stack_top;

//booking 1024 byte located by .bss through un initialized of int 256 element (256*4 = 1024_
static unsigned long stack_top[256];



void (* const g_cp_fn_vectors[] )() __attribute__((section(".vectors"))) = {
	
	(void(*)()) ((unsigned long )stack_top + (sizeof(stack_top) )),
	 &Reset_Handler,
	 &NMI_Handler,
	 &H_Fault_Handler,
	 &MM_Fault_Handler,
	 &Bus_Fault_Handler,
	 &Usage_Fault_Handler
	
	
};


void Reset_Handler ()
{
	//copy data section from flash to ram
	unsigned int DATA_size = (unsigned char*) &_E_DATA - (unsigned char*) &_S_DATA ;
	
	unsigned char* P_src = (unsigned char*) &_E_text;
	unsigned char* P_des = (unsigned char*) &_S_DATA;
	
	int i;
	for(i = 0 ; i < DATA_size ; i++)
	{
		*((unsigned char*)P_des++) = *((unsigned char*)P_src++);
	}
	
	// init .bss section in sram and initialise it by 0
	
	unsigned int bss_size = (unsigned char*) &_E_bss - (unsigned char*) &_S_bss ;
	P_des = (unsigned char*) &_E_DATA;
	
		for(i = 0 ; i < bss_size ; i++)
	{
		*((unsigned char*)P_des++) = 0 ;
	}
	
	
	//jump to main
	main();
}
