#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_reg.h"
#include "GIE_interface.h"


void GIE_voidEnableGeneralInterrupts(void){
	__asm volatile("SEI"); /*Set Bit Interrupt */
	/*SET_BIT(SREG , SREG_I )*/
}
void GIE_voidDisableGeneralInterrupts(void){
		__asm volatile("CLI"); /*Clear Bit Interrupt */
	/*CLR_BIT(SREG , SREG_I )*/
	
}

