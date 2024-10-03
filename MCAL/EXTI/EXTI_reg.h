#ifndef EXTI_REG_H
#define EXTI_REG_H

#define GICR *((volatile uint8*) 0x5B) /*Genral Interrupt control register*/
#define GICR_INT0   6u   /*INT0 Bit*/
#define GICR_INT1	7u	/*INT1 Bit*/
#define GICR_INT2	5u	/*INT2 Bit*/

#define MCUCR *((volatile uint8*) 0x55) /*MCU CONTROL REGISTER*/
#define MCUCR_ISC00  0u    		/*INT0 SENSE CONTROL BIT 0*/
#define MCUCR_ISC01	 1u			/*INT0 SENSE CONTROL BIT 1*/
#define MCUCR_ISC10	 2u			/*INT1 SENSE CONTROL BIT 0*/
#define MCUCR_ISC11  3u			/*INT1 SENSE CONTROL BIT 1*/


#define MCUCSR *((volatile uint8*) 0x54)  /*MCU control & status register*/
#define MCUCSR_ISC2 6u   /*INT2 SENSE CONTROL */ 

#endif