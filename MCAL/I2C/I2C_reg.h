#ifndef I2C_REG_H
#define I2C_REG_H

#define  TWDR   *((volatile uint8*) 0x23)  /*Two wire serial interface data register*/


#define  TWAR   *((volatile uint8*) 0x22)  /*Two wire serial addresses register*/


#define  TWSR   *((volatile uint8*) 0x21)  /*Two wire serial addresses register*/


#define  TWBR   *((volatile uint8*) 0x20)  /*Two wire serial Bit register*/

#define  TWCR   *((volatile uint8*) 0x56)
#define TWCR_TWEA             6u
#define TWCR_TWINT            7u
#define TWCR_TWSTA             5u
#define TWCR_TWSTO              4u
#define TWCR_TWEN              2u
#endif
