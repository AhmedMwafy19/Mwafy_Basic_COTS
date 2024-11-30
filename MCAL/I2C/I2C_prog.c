#include "STD_TYPES.h"
#include "ErrorState.h"
#include "BIT_MATH.h"

#include "I2C_reg.h"
#include "I2C_prv.h"
#include "I2C_interface.h"
#include "I2C_cfg.h"

uint8 I2C_u8MasterInit(uint8 Copy_u8Address){
	uint8 Local_u8ErrorState = OK ;
	if(Copy_u8Address == 0) {
		/*Do Nothing Don't Assign Address*/
	}
	else {
		if (Copy_u8Address >= 120u){
			Local_u8ErrorState = I2C_SLA_INVALID ;
		}
		else {
			TWAR = (Copy_u8Address << 1) ;
		}
	}
	/*Setting BitRate*/
	TWBR =( (uint8)((uint32) MCU_CLK_FREQUENCY / (uint32) SCL_CLK ) - 16 ) / 2 ;
	SET_BIT(TWCR , TWCR_TWEA); /*Enabling Ack bit*/
	return Local_u8ErrorState ;
}
uint8 I2C_u8SlaveInit(uint8 Copy_u8Address){
	uint8 Local_u8ErrorState = OK ;
		if (Copy_u8Address >= 120u){
			Local_u8ErrorState = I2C_SLA_INVALID ;
		}
		else {
			TWAR = (Copy_u8Address << 1) ;
		}
		/*Setting BitRate*/
		TWBR =( (uint8)((uint32) MCU_CLK_FREQUENCY / (uint32) SCL_CLK ) - 16 ) / 2 ;
		SET_BIT(TWCR , TWCR_TWEA); /*Enabling Ack bit*/
	return Local_u8ErrorState ;
}


void I2C_voidSendStartCondition(void){
	/*Enabling I2C*/
	SET_BIT(TWCR , TWCR_TWEN);

	/*Sending Start Condition*/
	SET_BIT(TWCR , TWCR_TWSTA) ;
	/*Clearing the flag*/
		SET_BIT(TWCR , TWCR_TWINT);
	/*Waiting For Flag To rise*/
	while(GET_BIT(TWCR , TWCR_TWINT) != 1);

	CLR_BIT(TWCR , TWCR_TWSTA) ;
}
//void I2C_voidSendRepeatedStartCondition(void);
void I2C_voidSendStopCondition(void){
	/*Enabling I2C*/
	SET_BIT(TWCR , TWCR_TWEN);
	/*Sending Stop Condition*/
	SET_BIT(TWCR , TWCR_TWSTO) ;

	/*Clearing the flag*/
	SET_BIT(TWCR , TWCR_TWINT);

	/*Waiting For Flag To rise*/
	while(GET_BIT(TWCR , TWCR_TWINT) != 1);

}


void I2C_voidSendSLA_W(uint8 Copy_u8Address){
	TWDR = (Copy_u8Address << 1u) ;
	SET_BIT(TWDR , 0u);
	/*Clearing the flag*/
		SET_BIT(TWCR , TWCR_TWINT);
		/*Waiting For Flag To rise*/
		while(GET_BIT(TWCR , TWCR_TWINT) != 1);
}
void I2C_voidSendSLA_R(uint8 Copy_u8Address){
	TWDR = (Copy_u8Address << 1u) ;
	CLR_BIT(TWDR , 0u);
	/*Clearing the flag*/
		SET_BIT(TWCR , TWCR_TWINT);
		/*Waiting For Flag To rise*/
		while(GET_BIT(TWCR , TWCR_TWINT) != 1);
}



void I2C_voidMasterSendDataByte(uint8 Copy_u8Data){
	TWDR = Copy_u8Data ;

	/*Clearing the flag*/
		SET_BIT(TWCR , TWCR_TWINT);
		/*Waiting For Flag To rise*/
		while(GET_BIT(TWCR , TWCR_TWINT) != 1);
}
uint8 I2C_u8MasterRecieveDataByte(uint8 * Copy_u8Data){
	uint8 Local_u8ErrorState = OK;
	if(Copy_u8Data != NULL){
		*Copy_u8Data = TWDR ;
		/*Clearing the flag*/
			SET_BIT(TWCR , TWCR_TWINT);
			/*Waiting For Flag To rise*/
			while(GET_BIT(TWCR , TWCR_TWINT) != 1);
	}
	else {
		Local_u8ErrorState = NULL_PTR_ERR ;
	}
	return Local_u8ErrorState ;
}


