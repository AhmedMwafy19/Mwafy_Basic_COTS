#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrorState.h"

#include "TWI_reg.h"
#include "TWI_prv.h"
#include "TWI_interface.h"
#include "TWI_cfg.h"


/*If master isn't an address in network pass 0*/
void TWI_voidMasterInit(uint8 Copy_u8Address){
	uint32 Local_u32TWI_CLK_SYS = 0;
	if(Copy_u8Address == 0) {
		/*Do Nothing Don't Assign Address*/
	}
	else {
		/*Master is Addressed in network & assign the address*/
		TWAR = ( Copy_u8Address << 1u );
	}
	/*Setting Prescalar bits*/
#if TWI_PRESCALAR == DIVISION_BY_ONE
	CLR_BIT(TWSR , TWSR_TWPS1);
	CLR_BIT(TWSR , TWSR_TWPS0);
	Local_u32TWI_CLK_SYS = ( uint32 )MCU_CLK_FREQUENCY ;
#elif TWI_PRESCALAR == DIVISION_BY_FOUR
	CLR_BIT(TWSR , TWSR_TWPS1);
	SET_BIT(TWSR , TWSR_TWPS0);
	Local_u32TWI_CLK_SYS = ( uint32 )MCU_CLK_FREQUENCY / 4u ;
#elif TWI_PRESCALAR == DIVISION_BY_16
	SET_BIT(TWSR , TWSR_TWPS1);
	CLR_BIT(TWSR , TWSR_TWPS0);
	Local_u32TWI_CLK_SYS = ( uint32 )MCU_CLK_FREQUENCY / 16u ;
#elif TWI_PRESCALAR == DIVISION_BY_64
	SET_BIT(TWSR , TWSR_TWPS1);
	SET_BIT(TWSR , TWSR_TWPS0);
	Local_u32TWI_CLK_SYS = ( uint32 )MCU_CLK_FREQUENCY / 64u ;
#else
#error Wrong Configuration choice
#endif
	/*Setting BitRate*/
	TWBR =( (uint8)(Local_u32TWI_CLK_SYS / (uint32) SCL_CLK ) - 16 ) / 2 ;

	/*Enabling Acknowledge Bit*/
	SET_BIT(TWCR , TWCR_TWEA);

	/*TWI Enable*/
	SET_BIT(TWCR , TWCR_TWEN);

}


void TWI_voidSlaveInit(uint8 Copy_u8Address){
	uint32 Local_u32TWI_CLK_SYS = 0;
	if(Copy_u8Address >= 120) {
		/*Do Nothing Don't Assign Address*/
		return;
	}
	else {
		/*Slave is Addressed Correctly in network & assign the address*/
			TWAR = ( Copy_u8Address << 1u );
	}
	/*Setting Prescalar bits*/
#if TWI_PRESCALAR == DIVISION_BY_ONE
	CLR_BIT(TWSR , TWSR_TWPS1);
	CLR_BIT(TWSR , TWSR_TWPS0);
	Local_u32TWI_CLK_SYS = ( uint32 )MCU_CLK_FREQUENCY ;
#elif TWI_PRESCALAR == DIVISION_BY_FOUR
	CLR_BIT(TWSR , TWSR_TWPS1);
	SET_BIT(TWSR , TWSR_TWPS0);
	Local_u32TWI_CLK_SYS = ( uint32 )MCU_CLK_FREQUENCY / 4u ;
#elif TWI_PRESCALAR == DIVISION_BY_16
	SET_BIT(TWSR , TWSR_TWPS1);
	CLR_BIT(TWSR , TWSR_TWPS0);
	Local_u32TWI_CLK_SYS = ( uint32 )MCU_CLK_FREQUENCY / 16u ;
#elif TWI_PRESCALAR == DIVISION_BY_64
	SET_BIT(TWSR , TWSR_TWPS1);
	SET_BIT(TWSR , TWSR_TWPS0);
	Local_u32TWI_CLK_SYS = ( uint32 )MCU_CLK_FREQUENCY / 64u ;
#else
#error Wrong Configuration choice
#endif
	/*Setting BitRate*/
	TWBR =( (uint8)(Local_u32TWI_CLK_SYS / (uint32) SCL_CLK ) - 16 ) / 2 ;

	/*Enabling Acknowledge Bit*/
	SET_BIT(TWCR , TWCR_TWEA);

	/*TWI Enable*/
	SET_BIT(TWCR , TWCR_TWEN);

}



TWI_ErrorState_t TWI_enuSendStartCondition(void){
	TWI_ErrorState_t Local_enuErrState = TWI_NoErr ;

	/*Setting Start Condition Bit*/
	SET_BIT(TWCR,TWCR_TWSTA);

	/*Clear interrupt flag to enable previous operation to happen*/
	SET_BIT(TWCR , TWCR_TWINT);

	/*Waiting For Flag To rise*/
	while(GET_BIT(TWCR , TWCR_TWINT) == 0u);

	/*Checking Status Register*/
	if((TWSR & STATUS_BITS_MASK) != START_ACK){
		Local_enuErrState = TWI_StartCondErr;
	}
	else {
		/*Do Nothing*/
	}


	return Local_enuErrState ;
}



TWI_ErrorState_t TWI_enuSendRepeatedStartCondition(void){
	TWI_ErrorState_t Local_enuErrState = TWI_NoErr ;

	/*Setting Start Condition Bit*/
	SET_BIT(TWCR,TWCR_TWSTA);

	/*Clear interrupt flag to enable previous operation to happen*/
	SET_BIT(TWCR , TWCR_TWINT);

	/*Waiting For Flag To rise*/
	while(GET_BIT(TWCR , TWCR_TWINT) == 0u);

	/*Checking Status Register*/
	if((TWSR & STATUS_BITS_MASK) != REP_START_ACK){
		Local_enuErrState = TWI_Rep_StartCondErr;
	}
	else {
	/*Do Nothing*/
	}


	return Local_enuErrState ;
}



TWI_ErrorState_t TWI_enuSendSlaveAdd_WR(uint8 Copy_u8SlaveAddress){
	TWI_ErrorState_t Local_enuErrState = TWI_NoErr ;
	/*Sending Slave Address*/
	TWDR = (Copy_u8SlaveAddress << 1u) ;
	/*Configuring it to write request*/
	CLR_BIT(TWDR , 0u);
	/*Clearing The Starting Condition Bit ( Transmission was successful )*/
	CLR_BIT(TWCR , TWCR_TWSTA) ;
	/*Clearing the flag*/
	SET_BIT(TWCR , TWCR_TWINT);
	/*Waiting For Flag To rise*/
	while(GET_BIT(TWCR , TWCR_TWINT) == 0u);


	/*Checking Status Register*/
		if((TWSR & STATUS_BITS_MASK) != SLAVE_ADD_AND_WRITE_ACK){
			Local_enuErrState = TWI_Slave_Add_WR_Err;
		}
		else {
		/*Do Nothing*/
		}
		return Local_enuErrState ;

}


TWI_ErrorState_t TWI_enuSendSlaveAdd_RD(uint8 Copy_u8SlaveAddress){
	TWI_ErrorState_t Local_enuErrState = TWI_NoErr ;
	/*Sending Slave Address*/
	TWDR = (Copy_u8SlaveAddress << 1u) ;
	/*Configuring it to Read request*/
	SET_BIT(TWDR , 0u);
	/*Clearing The Starting Condition Bit ( Transmission was successful )*/
	CLR_BIT(TWCR , TWCR_TWSTA) ;
	/*Clearing the flag*/
	SET_BIT(TWCR , TWCR_TWINT);
	/*Waiting For Flag To rise*/
	while(GET_BIT(TWCR , TWCR_TWINT) == 0u);


	/*Checking Status Register*/
		if((TWSR & STATUS_BITS_MASK) != SLAVE_ADD_AND_READ_ACK){
			Local_enuErrState = TWI_Slave_Add_RD_Err;
		}
		else {
		/*Do Nothing*/
		}
		return Local_enuErrState ;
}



TWI_ErrorState_t TWI_enuSendDataByte(uint8 Copy_u8Data){
	TWI_ErrorState_t Local_enuErrState = TWI_NoErr ;
	/*Writing Data Byte to the data register*/
	TWDR = Copy_u8Data ;
	/*Clearing the flag*/
	SET_BIT(TWCR , TWCR_TWINT);
	/*Waiting For Flag To rise*/
	while(GET_BIT(TWCR , TWCR_TWINT) == 0u);


	/*Checking Status Register*/
		if((TWSR & STATUS_BITS_MASK) != MASTER_WR_BYTE_ACK){
			Local_enuErrState = TWI_DataByte_Sent_ERR;
		}
		else {
		/*Do Nothing*/
		}

	return Local_enuErrState ;

}



TWI_ErrorState_t TWI_enuReceiveDataByte(uint8  * Copy_u8Data){
	TWI_ErrorState_t Local_enuErrState = TWI_NoErr ;
	/*Checking The validity of the pointer*/
	if(Copy_u8Data == NULL){
		return TWI_NULL_PTR_ERR;
	}
	else {
		/*Clearing the flag*/
		SET_BIT(TWCR , TWCR_TWINT);
	/*Waiting For Flag To rise*/
	while(GET_BIT(TWCR , TWCR_TWINT) == 0u);


	/*Checking Status Register*/
		if((TWSR & STATUS_BITS_MASK) != MASTER_RD_BYTE_ACK){
			Local_enuErrState = TWI_DataByte_Received_ERR;
		}
		else {
		/*Writing Data Byte to the data register*/
			*Copy_u8Data = TWDR ;
		}

	}
	return Local_enuErrState ;

}



void TWI_voidSendStopCondition(void){
	/*Setting Stop Condition Bit*/
	SET_BIT(TWCR , TWCR_TWSTO);
	/*Clearing the flag*/
	SET_BIT(TWCR , TWCR_TWINT);
	/*Waiting For Flag To rise*/
	while(GET_BIT(TWCR , TWCR_TWINT) == 0u);

}

