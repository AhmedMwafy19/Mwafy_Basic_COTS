/*
 * main.c
 *
 *  Created on: Nov 9, 2024
 *      Author: Computec
 */
#include "STD_TYPES.h"
#include "ErrorState.h"

#include "DIO_interface.h"
#include "SPI_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
void main(void){
	PORT_voidInit();
	SPI_voidInit();
	CLCD_voidInit();
  uint8 Local_u8Data ;


  while(1){
	  Local_u8Data = SPI_u8TransceiveSynch('a');

	  switch(Local_u8Data){
	  case '1' :CLCD_voidSendNumber(1);
	  	  break;
	  case '2' :CLCD_voidSendNumber(2);
	  	  break;
	  case '3' :CLCD_voidSendNumber(3);
	  	  break;
	  case '4' :CLCD_voidSendNumber(4);
	  break;
	  case '5' :CLCD_voidSendNumber(5);
	  break;
	  default: CLCD_voidSendCommand(1);


	  }
  }
}
