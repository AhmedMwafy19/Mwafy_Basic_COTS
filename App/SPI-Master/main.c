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
#include <util/delay.h>
void main(void){
	PORT_voidInit();
	SPI_voidInit();

  uint8 Local_u8Data , Local_u8Button;
  Local_u8Data = 0 ;

  while(1){

	 do{
		 DIO_u8ReadPinValue(DIO_u8PORTC ,DIO_u8PIN1 , &Local_u8Button);
	 }while(Local_u8Button ==DIO_u8PINVALUE_HIGH);

	 do{
			 DIO_u8ReadPinValue(DIO_u8PORTC ,DIO_u8PIN1 , &Local_u8Button);
		 }while(Local_u8Button ==DIO_u8PINVALUE_LOW);

	  Local_u8Data ++ ;

	  DIO_u8SetPinValue(DIO_u8PORTC , DIO_u8PIN4 , DIO_u8PINVALUE_LOW);
	  SPI_u8TransceiveSynch(Local_u8Data + '0');
	  DIO_u8SetPinValue(DIO_u8PORTC , DIO_u8PIN4 , DIO_u8PINVALUE_HIGH);

	 if(Local_u8Data == 5){
		 Local_u8Data = 0 ;
	 }

  }
}
