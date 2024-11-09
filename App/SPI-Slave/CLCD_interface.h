#ifndef CLCD_INTERFACE_H
#define CLCD_INTERFACE_H

void CLCD_voidSendCommand(uint8 Copy_u8Cmd);
void CLCD_voidSendData(uint8 Copy_u8Data);
void CLCD_voidInit(void);
uint8 CLCD_u8SendString(const char *Copy_pu8String);
void CLCD_voidSendNumber(sint32 Copy_s32Number);
void CLCD_voidGoToXY(uint8 Copy_u8X,uint8 Copy_u8Y);
uint8 CLCD_u8SendMadeCharacters(uint8 Copy_u8LocationNumber,char *Copy_pu8CharacterDesign,uint8 Copy_u8X,uint8 Copy_u8Y);
#endif
