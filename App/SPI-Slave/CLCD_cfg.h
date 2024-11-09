#ifndef CLCD_CFG_H
#define CLCD_CFG_H

/*choose from 1-FOUR_BIT
 * 			  2-EIGHT_BIT*/
#define CLCD_BITMODE  FOUR_BIT

/*Configure whether the CLCD RW pin is connected to a DIO pin or directly to the gnd, options:
  	1- GND_CONNECTED
  	2- DIO_CONNECTED
 	*/
#define CLCD_u8RW_CONNECTION GND_CONNECTED
/*set contrl port*/
#define CLCD_u8CTRL_PORT DIO_u8PORTA
/*set control pins*/
#define CLCD_u8RS_PIN DIO_u8PIN1
#if CLCD_u8RW_CONNECTION == DIO_CONNECTED
#define CLCD_u8RW_PIN DIO_u8PIN3
#endif
#define CLCD_u8E_PIN DIO_u8PIN2
/*Set data port*/
#define CLCD_u8DATA_PORT DIO_u8PORTA

#if CLCD_BITMODE == FOUR_BIT  //just in case of 4 bits connection
#define CLCD_D4_PIN DIO_u8PIN3
#define CLCD_D5_PIN DIO_u8PIN4
#define CLCD_D6_PIN DIO_u8PIN5
#define CLCD_D7_PIN DIO_u8PIN6
#endif


#endif
