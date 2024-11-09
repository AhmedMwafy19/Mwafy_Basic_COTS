#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#include "ErrorState.h"

#include "DIO_interface.h" //Always include the lower layer & file included is always interface file
#include "CLCD_prv.h"
#include "CLCD_cfg.h"
#include "CLCD_interface.h"
#if CLCD_BITMODE == FOUR_BIT
static void CLCD_voidSetFourDataPins(uint8 Copy_u8Data){
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_D4_PIN,GET_BIT(Copy_u8Data,0));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_D5_PIN,GET_BIT(Copy_u8Data,1));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_D6_PIN,GET_BIT(Copy_u8Data,2));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_D7_PIN,GET_BIT(Copy_u8Data,3));
}
#endif
static void CLCD_voidEnable(void){

	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN,DIO_u8PINVALUE_HIGH);
		_delay_ms(2);
		DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN,DIO_u8PINVALUE_LOW);


}

void CLCD_voidSendCommand(uint8 Copy_u8Cmd){
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RS_PIN,DIO_u8PINVALUE_LOW);
#if CLCD_u8RW_CONNECTION == DIO_CONNECTED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RW_PIN,DIO_u8PINVALUE_LOW);
#endif
#if CLCD_BITMODE == EIGHT_BIT
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,Copy_u8Cmd);
	CLCD_voidEnable();
#elif CLCD_BITMODE == FOUR_BIT
 CLCD_voidSetFourDataPins(Copy_u8Cmd>>4);
	CLCD_voidEnable();
	CLCD_voidSetFourDataPins(Copy_u8Cmd);
	CLCD_voidEnable();
#else
#error wrong CLCD_BIT_MODE configuration option
#endif
	

}
void CLCD_voidSendData(uint8 Copy_u8Data){
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RS_PIN,DIO_u8PINVALUE_HIGH);
#if CLCD_u8RW_CONNECTION == DIO_CONNECTED
		DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RW_PIN,DIO_u8PINVALUE_LOW);
#endif
#if CLCD_BITMODE == EIGHT_BIT
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,Copy_u8Data);
	CLCD_voidEnable();
#elif CLCD_BITMODE == FOUR_BIT
 CLCD_voidSetFourDataPins(Copy_u8Data>>4);
	CLCD_voidEnable();
	CLCD_voidSetFourDataPins(Copy_u8Data);
	CLCD_voidEnable();
#else
#error wrong CLCD_BIT_MODE configuration option
#endif

}
void CLCD_voidInit(void){
	_delay_ms(40);/*Wait for more than 30 ms after power on*/

#if CLCD_BITMODE == FOUR_BIT
		CLCD_voidSetFourDataPins(0b0010);
		CLCD_voidEnable();
		CLCD_voidSetFourDataPins(0b0010);
		CLCD_voidEnable();
		CLCD_voidSetFourDataPins(0b1000);
		CLCD_voidEnable();
#elif CLCD_BITMODE == EIGHT_BIT
	CLCD_voidSendCommand(0b00111000);

#endif	/*Function set command: 2 lines, Font size: 5x7*/
	CLCD_voidSendCommand(0b00001100);/*Display on off control : Display on, cursor off, blink cursor off*/
	CLCD_voidSendCommand(1);/*clear display*/


}

uint8 CLCD_u8SendString(const char *Copy_pu8String){
	uint8 Local_u8ErrorState=OK;
	if(Copy_pu8String!=NULL){
	while(*Copy_pu8String!='\0'){
		CLCD_voidSendData(*Copy_pu8String);
		Copy_pu8String++;
	}
}
	else{
		Local_u8ErrorState=NULL_PTR_ERR;}

	return Local_u8ErrorState;
}

void CLCD_voidSendNumber(sint32 Copy_s32Number){
	uint8 Local_u8Remainder,Local_u8count=0;
	sint8 Local_s8LoopCounter;
	uint32 Local_u8Array[10];
	if(Copy_s32Number<0){
		CLCD_voidSendData('-');
		Copy_s32Number*=-1;
	}
	else if(Copy_s32Number==0){
		CLCD_voidSendData('0');
	}
	while(Copy_s32Number!=0) {
	        Local_u8Remainder=(uint8)(Copy_s32Number%10);
	        Local_u8Array[Local_u8count]=Local_u8Remainder;
	        Local_u8count++;
	        Copy_s32Number/=10;
	    }
	for(Local_s8LoopCounter=(sint8)Local_u8count-1;Local_s8LoopCounter>=0;Local_s8LoopCounter--){
	 CLCD_voidSendData(Local_u8Array[Local_s8LoopCounter]+48);
}
}

void CLCD_voidGoToXY(uint8 Copy_u8X,uint8 Copy_u8Y){
	uint8 Local_u8DDRAMAddress;
	Local_u8DDRAMAddress = Copy_u8Y * 0x40 + Copy_u8X;
	SET_BIT(Local_u8DDRAMAddress,7);
	CLCD_voidSendCommand(Local_u8DDRAMAddress);
}


uint8 CLCD_u8SendMadeCharacters(uint8 Copy_u8LocationNumber,char *Copy_pu8CharacterDesign,uint8 Copy_u8X,uint8 Copy_u8Y){
	uint8 Local_u8LocationAddress=Copy_u8LocationNumber*8;
	uint8 Local_u8ErrorState=OK;
	if(Copy_pu8CharacterDesign!=NULL){
	SET_BIT(Local_u8LocationAddress,6);
	CLCD_voidSendCommand(Local_u8LocationAddress);

	for(uint8 Local_u8LoopCounter=0;Local_u8LoopCounter<8;Local_u8LoopCounter++){
		CLCD_voidSendData(Copy_pu8CharacterDesign[Local_u8LoopCounter]);
	}

	CLCD_voidGoToXY(Copy_u8X,Copy_u8Y);
	CLCD_voidSendData(Copy_u8LocationNumber);
	}
	else Local_u8ErrorState=NULL_PTR_ERR;
	return Local_u8ErrorState;


}
