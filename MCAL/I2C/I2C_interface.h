#ifndef I2C_INTERFACE_H
#define I2C_INTERFACE_H

uint8 I2C_u8MasterInit(uint8 Copy_u8Address);
uint8 I2C_u8SlaveInit(uint8 Copy_u8Address);

void I2C_voidSendStartCondition(void);
//void I2C_voidSendRepeatedStartCondition(void);

void I2C_voidSendSLA_W(uint8 Copy_u8Address);
void I2C_voidSendSLA_R(uint8 Copy_u8Address);

void I2C_voidMasterSendDataByte(uint8 Copy_u8Data);
uint8 I2C_u8MasterRecieveDataByte(uint8 * Copy_u8Data);

void I2C_voidSendStopCondition(void);
#endif
