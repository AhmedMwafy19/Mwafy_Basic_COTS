#ifndef MOTOR_INTERFACE_H
#define MOTOR_INTERFACE_H
typedef struct{
	uint8 Connection_Port; /*Which Port Motor Is connected to*/
	uint8 Pin1Connection; /*When this pin is high , Motor rotates cw*/
	uint8 Pin2Connection;/*When this pin is high , Motor rotates ccw*/
}MOTOR_CONNECTIONS;
/*Example for Configuring a motor in your application
MOTOR_CONNECTIONS Motor1 = {
	.Connection_Port = DIO_u8PORTC,
	.Pin1Connection = DIO_u8PIN0,
	.Pin2Connection = DIO_u8PIN1
};*/

uint8 MOTOR_u8RotateClockWise(MOTOR_CONNECTIONS * Copy_pstructMotor);
uint8 MOTOR_u8RotateCounterClockWise(MOTOR_CONNECTIONS * Copy_pstructMotor);
uint8 MOTOR_u8Stop(MOTOR_CONNECTIONS * Copy_pstructMotor);


#endif
