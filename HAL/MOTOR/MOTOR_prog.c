#include "STD_TYPES.h"
#include "ErrorState.h"

#include "DIO_interface.h"
#include "MOTOR_prv.h"
#include "MOTOR_interface.h"
#include "MOTOR_cfg.h"
#include "MOTOR_prv.h"

uint8 MOTOR_u8RotateClockWise(MOTOR_CONNECTIONS * Copy_pstructMotor){
	uint8 Local_u8ErrorState = OK;
	if(Copy_pstructMotor != NULL){/*Checking The validity of the pointer*/
		/*Start with low to protect the connection since it's h brigde it could cause the cct. to burn*/
		DIO_u8SetPinValue(Copy_pstructMotor -> Connection_Port , Copy_pstructMotor -> Pin2Connection,DIO_u8PINVALUE_LOW);
		DIO_u8SetPinValue(Copy_pstructMotor -> Connection_Port , Copy_pstructMotor -> Pin1Connection,DIO_u8PINVALUE_HIGH);
		/*Setting Pin1 Value High & pin2 Value Low for rotating cw*/
	}
	else {
		Local_u8ErrorState =NULL_PTR_ERR;
	}
	
	return Local_u8ErrorState;
}
uint8 MOTOR_u8RotateCounterClockWise(MOTOR_CONNECTIONS * Copy_pstructMotor){
	uint8 Local_u8ErrorState = OK;
	if(Copy_pstructMotor != NULL){/*Checking The validity of the pointer*/
			/*Start with low to protect the connection since it's h brigde it could cause the cct. to burn*/
			DIO_u8SetPinValue(Copy_pstructMotor -> Connection_Port , Copy_pstructMotor -> Pin1Connection,DIO_u8PINVALUE_LOW);
			DIO_u8SetPinValue(Copy_pstructMotor -> Connection_Port , Copy_pstructMotor -> Pin2Connection,DIO_u8PINVALUE_HIGH);
			/*Setting Pin2 Value High & pin1 Value Low for rotating ccw*/
		}
		else {
			Local_u8ErrorState =NULL_PTR_ERR;
		}
	return Local_u8ErrorState;
}
uint8 MOTOR_u8Stop(MOTOR_CONNECTIONS * Copy_pstructMotor){
	uint8 Local_u8ErrorState = OK;
	if(Copy_pstructMotor != NULL){/*Checking The validity of the pointer*/
			/*THis couldn't stop immediately if the hardware connection doesn't support it (No Not gate)*/
			DIO_u8SetPinValue(Copy_pstructMotor -> Connection_Port , Copy_pstructMotor -> Pin2Connection,DIO_u8PINVALUE_LOW);
			DIO_u8SetPinValue(Copy_pstructMotor -> Connection_Port , Copy_pstructMotor -> Pin1Connection,DIO_u8PINVALUE_LOW);
		}
		else {
			Local_u8ErrorState =NULL_PTR_ERR;
		}
	return Local_u8ErrorState;
}
