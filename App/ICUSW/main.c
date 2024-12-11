/*
 * main.c
 *
 *  Created on: Dec 11, 2024
 *      Author: Computec
 */
#include "STD_TYPES.h"
#include "ErrorState.h"

#include "PORT_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"
#include "TIMER_interface.h"
#include "CLCD_interface.h"
uint16 PeriodTicks = 0;
uint16 DutyTicks = 0;
TIMER0_cfg_t PWM_TIMER =
{
	.WFG_Mode = T0_FAST_PWM ,
	.Prescaler = TIMER_PRESCALER_DIVISION_64 ,
	.Out_HW_Opt = T0_OC0_FAST_PWM_CLRON_COM_SETON_TOP
};

TIMER1_cfg_t COUNTER_TIMER =
{
		.WFG_Mode = T1_NORMAL,
		.Prescaler = TIMER_PRESCALER_DIVISION_64
};

void ISR(void);
void main(void){
	PORT_voidInit();
	TIMER0_u8Init( &PWM_TIMER );
	TIMER0_voidSetCompareValue(20);
	TIMER1_u8Init( &COUNTER_TIMER );
	EXTI_u8SetSenseCtrl(INT0 , RISING_EGDE);
	EXTI_u8SetCallBack(INT0 , &ISR);
	CLCD_voidInit();
	EXTI_u8EnableIntChannel(INT0);
	GIE_voidEnableGeneralInterrupts();

	while(1){
		while(PeriodTicks == 0u && DutyTicks == 0u);

		CLCD_voidGoToXY(0,0);
		CLCD_voidSendNumber(DutyTicks);
		CLCD_voidGoToXY(0,1);
		CLCD_voidSendNumber(PeriodTicks);

	}
}
void ISR(void){
	volatile static uint8 Local_u8Counter = 0 ;
	Local_u8Counter ++ ;
	if(Local_u8Counter == 1u){
		TIMER1_voidSetTimerValue(0u);
	}
	else if(Local_u8Counter == 2u){
		PeriodTicks = TIMER1_u16ReadTimerVal() ;
		EXTI_u8SetSenseCtrl(INT0 , FALLING_EDGE);
	}
	else {
		DutyTicks = TIMER1_u16ReadTimerVal() - PeriodTicks ;
		EXTI_u8DisableIntChannel(INT0);
	}
}
