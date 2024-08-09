#ifndef KPD_CGF_H
#define KPD_CGF_H

#define KPD_COL_PORT DIO_u8PORTD
#define KPD_ROW_PORT DIO_u8PORTB

#define KPD_COL0_PIN DIO_u8PIN0
#define KPD_COL1_PIN DIO_u8PIN1
#define KPD_COL2_PIN DIO_u8PIN2
#define KPD_COL3_PIN DIO_u8PIN3

#define KPD_ROW0_PIN DIO_u8PIN4
#define KPD_ROW1_PIN DIO_u8PIN5
#define KPD_ROW2_PIN DIO_u8PIN6
#define KPD_ROW3_PIN DIO_u8PIN7

#define KPD_au8Array {{ 1 , 2 , 3 , 4 },{ 5 , 6 , 7 , 8 },{ 9 , 10 , 11 , 12 },{ 13 , 14 , 15 , 16 }}

#define KPD_NOTPRESSED 0xff


#endif
