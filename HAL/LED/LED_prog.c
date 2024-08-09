#include "STD_TYPES.h"
#include "ErrorState.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "LED_prv.h"
#include "LED_interface.h"
#include "LED_cfg.h"

uint8 LED_u8TurnOn(const LED_CONFIGURATION * Copy_pstructLed){
	uint8 Local_u8ErrorState = OK;

	if(Copy_pstructLed != NULL){ //check the validity of the pointer
	if(Copy_pstructLed -> LED_u8ACTIVETYPE == ACTIVE_HIGH){

		DIO_u8SetPinValue(Copy_pstructLed -> LED_u8PORT,Copy_pstructLed -> LED_u8PIN,DIO_u8PINVALUE_HIGH);
	/*Setting pin value to high to activate The led which is active high*/
	}
	else if(Copy_pstructLed -> LED_u8ACTIVETYPE == ACTIVE_LOW){

		DIO_u8SetPinValue(Copy_pstructLed -> LED_u8PORT,Copy_pstructLed -> LED_u8PIN,DIO_u8PINVALUE_LOW);
	/*Setting pin value to Low to activate The led which is active low*/
	}
	else Local_u8ErrorState = NOK; //invalid active type for led
	}
	else Local_u8ErrorState = NULL_PTR_ERR; // pointer contains an invalid address

	return Local_u8ErrorState;
	
}
uint8 LED_u8TurnOff(const LED_CONFIGURATION * Copy_pstructLed){
	uint8 Local_u8ErrorState = OK;

		if(Copy_pstructLed != NULL){ //check the validity of the pointer
		if(Copy_pstructLed -> LED_u8ACTIVETYPE == ACTIVE_HIGH){

			DIO_u8SetPinValue(Copy_pstructLed -> LED_u8PORT,Copy_pstructLed -> LED_u8PIN,DIO_u8PINVALUE_LOW);
		/*Setting pin value to LOW to deactivate The led which is active high*/
		}
		else if(Copy_pstructLed -> LED_u8ACTIVETYPE == ACTIVE_LOW){

			DIO_u8SetPinValue(Copy_pstructLed -> LED_u8PORT,Copy_pstructLed -> LED_u8PIN,DIO_u8PINVALUE_HIGH);
		/*Setting pin value to HIGH to deactivate The led which is active low*/
		}
		else Local_u8ErrorState = NOK; //invalid active type for led
		}
		else Local_u8ErrorState = NULL_PTR_ERR; // pointer contains an invalid address

		return Local_u8ErrorState;

	
	
}
uint8 LED_u8ToggleLed(const LED_CONFIGURATION * Copy_pstructLed){
	uint8 Local_u8ErrorState = OK;
	uint8 Local_u8PinState;
		if(Copy_pstructLed != NULL){ //check the validity of the pointer

			DIO_u8ReadPinValue(Copy_pstructLed -> LED_u8PORT, Copy_pstructLed -> LED_u8PIN,&Local_u8PinState);
			/*Read Pin status to led is on or off */
			if(Local_u8PinState==DIO_u8PINVALUE_LOW){

				LED_u8TurnOn(Copy_pstructLed);

			}

			else if(Local_u8PinState==DIO_u8PINVALUE_HIGH){

				LED_u8TurnOff(Copy_pstructLed);

			}

}
			else Local_u8ErrorState = NULL_PTR_ERR;

			return Local_u8ErrorState; // pointer contains an invalid address
}
