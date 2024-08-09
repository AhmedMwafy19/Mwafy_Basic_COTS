#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H

void CLCD_voidSendCommand(uint8 Copy_u8Cmd);
void CLCD_voidSendData(uint8 Copy_u8Data);
void CLCD_voidInit(void);
uint8 CLCD_u8SendString(const char *Copy_pu8String);
void CLCD_voidSendNumber(sint32 Copy_s32Number);
#endif
