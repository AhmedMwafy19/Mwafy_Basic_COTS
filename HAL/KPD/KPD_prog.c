#include "STD_TYPES.h"
#include "ErrorState.h"

#include "DIO_interface.h"
#include "KPD_prv.h"
#include "KPD_interface.h"
#include "KPD_cfg.h"

uint8 KPD_u8GetKPDValue(uint8 * Copy_u8KPDValue){
	uint8 Local_u8ErrorState = OK , Local_u8LoopCounter1 , Local_u8LoopCounter2 ,Local_u8State = KPD_NOTPRESSED;
	uint8 Local_au8COLARR[KPD_COLNUM]= {KPD_COL0_PIN , KPD_COL1_PIN ,KPD_COL2_PIN , KPD_COL3_PIN };
	uint8 Local_au8ROWARR[KPD_ROWNUM]= {KPD_ROW0_PIN , KPD_ROW1_PIN ,KPD_ROW2_PIN , KPD_ROW3_PIN };

	uint8 Local_au8KPDArray[KPD_ROWNUM][KPD_COLNUM] = KPD_au8Array ; //Defined in configuration file
	if(Copy_u8KPDValue != NULL){ /*Checking The Validity of The pointers*/

		*Copy_u8KPDValue=KPD_NOTPRESSED;//initialize it to not pressed
		
		for(Local_u8LoopCounter1=0 ; Local_u8LoopCounter1 < KPD_COLNUM ; Local_u8LoopCounter1++ ){
/*Activate The current column*/
			DIO_u8SetPinValue(KPD_COL_PORT,Local_au8COLARR[Local_u8LoopCounter1],DIO_u8PINVALUE_LOW);
/*Activate the Rows*/
			for(Local_u8LoopCounter2=0 ; Local_u8LoopCounter2 < KPD_ROWNUM ; Local_u8LoopCounter2++ ){
				/*Reading The state of the current button*/

				DIO_u8ReadPinValue(KPD_ROW_PORT,Local_au8ROWARR[Local_u8LoopCounter2],&Local_u8State);

				if(Local_u8State == DIO_u8PINVALUE_LOW){

					*Copy_u8KPDValue = Local_au8KPDArray[Local_u8LoopCounter2][Local_u8LoopCounter1];
					/*Dealing with the waiting until the key is released*/

					while(Local_u8State==DIO_u8PINVALUE_LOW){

						DIO_u8ReadPinValue(KPD_ROW_PORT,Local_au8ROWARR[Local_u8LoopCounter2],&Local_u8State);

					}

					return Local_u8ErrorState ; /* To End the Function & save time*/

				}
			}
			/*Deactivate the current column*/
			DIO_u8SetPinValue(KPD_COL_PORT,Local_au8COLARR[Local_u8LoopCounter1],DIO_u8PINVALUE_HIGH);
		}
		
		
	}
	else {
		Local_u8ErrorState = NULL_PTR_ERR;
	}
	return Local_u8ErrorState ;
	
}
