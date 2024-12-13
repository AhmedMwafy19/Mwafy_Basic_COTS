#ifndef TWI_INTERFACE_H
#define TWI_INTERFACE_H

typedef enum 
{
	TWI_NoErr ,
	TWI_StartCondErr ,
	TWI_Rep_StartCondErr ,
	TWI_Slave_Add_WR_Err ,
	TWI_Slave_Add_RD_Err ,
	TWI_DataByte_Sent_ERR ,
	TWI_DataByte_Received_ERR ,
	TWI_NULL_PTR_ERR 
	
}TWI_ErrorState_t ;


/*If master isn't an address in network pass 0*/
void TWI_voidMasterInit(uint8 Copy_u8Address);
void TWI_voidSlaveInit(uint8 Copy_u8Address);

TWI_ErrorState_t TWI_enuSendStartCondition(void);
TWI_ErrorState_t TWI_enuSendRepeatedStartCondition(void);

TWI_ErrorState_t TWI_enuSendSlaveAdd_WR(uint8 Copy_u8SlaveAddress);
TWI_ErrorState_t TWI_enuSendSlaveAdd_RD(uint8 Copy_u8SlaveAddress);
TWI_ErrorState_t TWI_enuSendDataByte(uint8 Copy_u8Data);
TWI_ErrorState_t TWI_enuReceiveDataByte(uint8  * Copy_u8Data);

void TWI_voidSendStopCondition(void);

#endif
