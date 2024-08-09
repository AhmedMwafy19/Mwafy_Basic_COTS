#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ErrorState.h"

#include "DIO_interface.h"

#include "SSD_prv.h"

#include "SSD_interface.h"

#include "SSD_cfg.h"

uint8 SSDLED_u8ON(const SSD_CONFIGURATION * Copy_pstructSSD){


	uint8 Local_u8ErrorState = OK ;

	if(Copy_pstructSSD!=NULL){ //To check the validation of the pointer
		/*if conditions to turn on ssds depending on their type*/

		if(Copy_pstructSSD -> SSD_TYPE == COMMON_CATHODE || Copy_pstructSSD -> SSD_TYPE == ETA_KIT_COMMONANODE){

			DIO_u8SetPinValue(Copy_pstructSSD -> SSD_ENABLE_PORT,Copy_pstructSSD->SSD_ENABLE_PIN,DIO_u8PINVALUE_LOW);
	}

	else if(Copy_pstructSSD -> SSD_TYPE== COMMON_ANODE || Copy_pstructSSD-> SSD_TYPE== ETA_KIT_COMMONCATHODE){

		DIO_u8SetPinValue(Copy_pstructSSD -> SSD_ENABLE_PORT,Copy_pstructSSD->SSD_ENABLE_PIN,DIO_u8PINVALUE_HIGH);
	}

	else Local_u8ErrorState = NOK; //WrongInput
	}

	else Local_u8ErrorState=NULL_PTR_ERR; //pointer points to null

	return Local_u8ErrorState;
}
uint8 SSDLED_u8OFF(const SSD_CONFIGURATION * Copy_pstructSSD){
	uint8 Local_u8ErrorState = OK ;

		if(Copy_pstructSSD!=NULL){
			/*if conditions to turn off ssds depending on their type*/

			if(Copy_pstructSSD -> SSD_TYPE == COMMON_CATHODE || Copy_pstructSSD -> SSD_TYPE == ETA_KIT_COMMONANODE){
			DIO_u8SetPinValue(Copy_pstructSSD -> SSD_ENABLE_PORT,Copy_pstructSSD->SSD_ENABLE_PIN,DIO_u8PINVALUE_HIGH);
		}

			else if(Copy_pstructSSD -> SSD_TYPE== COMMON_ANODE || Copy_pstructSSD-> SSD_TYPE== ETA_KIT_COMMONCATHODE){
			DIO_u8SetPinValue(Copy_pstructSSD -> SSD_ENABLE_PORT,Copy_pstructSSD->SSD_ENABLE_PIN,DIO_u8PINVALUE_LOW);
		}

			else Local_u8ErrorState = NOK; //WrongInput
		}

		else Local_u8ErrorState=NULL_PTR_ERR; //pointer points to NULL

		return Local_u8ErrorState;
	
}
uint8 SSDLED_u8DisplayNumber(const SSD_CONFIGURATION * Copy_pstructSSD,uint8 Copy_u8Number){
	sint8 Local_s8LoopCounter;
	uint8 Local_u8ArrayNumbers[10]={
			0b00111111, //0
			0b00000110, //1
			0b01011011, //2
			0b01001111, //3
			0b01100110, //4
			0b01101101, //5
			0b01111101, //6
			0b00000111, //7
			0b01111111, //8
			0b01101111 //9
			};
	uint8 Local_u8ErrorState = OK,Local_u8Bit=6 ;
		if(Copy_pstructSSD!=NULL){
			/*if conditions to to know whether to led is turned on by High (common Cathode)
			 or Low(Common Anode)
			 */

			if(Copy_pstructSSD -> SSD_TYPE == COMMON_CATHODE || Copy_pstructSSD -> SSD_TYPE == ETA_KIT_COMMONCATHODE){

				for(Local_s8LoopCounter=(Copy_pstructSSD->SSD_LEDAPIN)+6u;Local_s8LoopCounter>=(Copy_pstructSSD->SSD_LEDAPIN);Local_s8LoopCounter--){

					DIO_u8SetPinValue(Copy_pstructSSD->SSD_LEDPORT,Local_s8LoopCounter,GET_BIT(Local_u8ArrayNumbers[Copy_u8Number],Local_u8Bit));

					Local_u8Bit--;
				}

			}

			else if(Copy_pstructSSD -> SSD_TYPE == COMMON_ANODE || Copy_pstructSSD -> SSD_TYPE == ETA_KIT_COMMONANODE){

				for(Local_s8LoopCounter=(Copy_pstructSSD->SSD_LEDAPIN)+6u;Local_s8LoopCounter>=(Copy_pstructSSD->SSD_LEDAPIN);Local_s8LoopCounter--){

					DIO_u8SetPinValue(Copy_pstructSSD->SSD_LEDPORT,Local_s8LoopCounter,!(GET_BIT(Local_u8ArrayNumbers[Copy_u8Number],Local_u8Bit)));

					Local_u8Bit--;

				}
			}

			else Local_u8ErrorState = NOK; //WrongInput

		}
	
		else Local_u8ErrorState=NULL_PTR_ERR; //pointer points to null

		return Local_u8ErrorState;
	}
