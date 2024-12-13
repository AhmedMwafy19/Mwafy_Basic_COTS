#include "STD_TYPES.h"
#include "ErrorState.h"
#include "util/delay.h"

#include "EEPROM_prv.h"
#include "EEPROM_cfg.h"
#include "EEPROM_interface.h"
#include "TWI_interface.h"
void EEPROM_voidSendByte(uint16 Copy_u16LocationAddress , uint8 Copy_u8Data){
	uint8 Local_u8AddressVariable = 0 ;
	Local_u8AddressVariable = ADDRESS_BIT_MASK | (A2_CONNECTION << 2u) | ( (Copy_u16LocationAddress >> 8u) & (3u) ) ;

	/*Sending Start Condition*/
	TWI_enuSendStartCondition();
	/*Sending Slave Address*/
	TWI_enuSendSlaveAdd_WR(Local_u8AddressVariable);
	/*Sending location address*/
	TWI_enuSendDataByte((uint8)Copy_u16LocationAddress);
	/*Sending Data*/
	TWI_enuSendDataByte(Copy_u8Data);
	/*Stop Condition*/
	TWI_voidSendStopCondition();
	_delay_ms(10);

}
uint8 EEPROM_u8RecieveByte(uint16 Copy_u16LocationAddress , uint8 * Copy_u8Data){
	uint8 Local_u8AddressVariable = 0 , Local_u8ErrorState = OK ;
	Local_u8AddressVariable = ADDRESS_BIT_MASK | (A2_CONNECTION << 2u) | ( (Copy_u16LocationAddress >> 8u) & (3u) ) ;

	if(Copy_u8Data == NULL){
		Local_u8ErrorState = NULL_PTR_ERR ;
	}
	else {
	/*Sending Start Condition*/
	TWI_enuSendStartCondition();
	/*Sending Slave Address*/
	TWI_enuSendSlaveAdd_RD(Local_u8AddressVariable);
	/*Sending location address*/
	TWI_enuSendDataByte((uint8)Copy_u16LocationAddress);
	/*Receive Data Data*/
	TWI_enuReceiveDataByte(Copy_u8Data);
	/*Stop Condition*/
	TWI_voidSendStopCondition();
	_delay_ms(10);

	}
	return Local_u8ErrorState ;
}
