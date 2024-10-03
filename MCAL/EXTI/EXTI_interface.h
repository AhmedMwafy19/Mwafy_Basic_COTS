#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H
typedef enum{
	INT0 ,
	INT1 ,
	INT2
}INT_CHANNEL;
typedef enum{
	LOW_LEVEL , 
	ON_CHANGE , 
	FALLING_EDGE , 
	RISING_EGDE
}SenseCtrl;

void EXTI_voidINIT(void);  /*To set interrupt pins & with its sense ctrls based on prebuilt configuartion*/

uint8 EXTI_u8SetSenseCtrl(INT_CHANNEL Copy_IntChannel , SenseCtrl Copy_SenseCtrl); /*To Change Sense control during run time*/

uint8 EXTI_u8EnableIntChannel(INT_CHANNEL Copy_IntChannel);
uint8 EXTI_u8DisableIntChannel(INT_CHANNEL Copy_IntChannel);

uint8 EXTI_u8SetCallBack(uint8 Copy_u8Channel , void(*Funcptr)(void));


#endif
