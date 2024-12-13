#ifndef EEPROM_INTERFACE_H
#define EEPROM_INTERFACE_H

void EEPROM_voidSendByte(uint16 Copy_u16LocationAddress , uint8 Copy_u8Data);
uint8 EEPROM_u8RecieveByte(uint16 Copy_u16LocationAddress , uint8 * Copy_u8Data);

#endif
