#ifndef TWI_PRV_H
#define TWI_PRV_H

#define  START_ACK          0x08   /*Start Has Been Sent*/
#define  REP_START_ACK          0x10   /*Repeated Start*/
#define  SLAVE_ADD_AND_WRITE_ACK         0x18   /*Master Transmit (Slave address + write request ACK )*/
#define  SLAVE_ADD_AND_READ_ACK         0x40   /*Master Transmit (Slave address + read request ACK )*/
#define  MASTER_WR_BYTE_ACK         0x28   /*Master transmit data ack*/
#define  MASTER_RD_BYTE_ACK         0x50   /*Master receive data ack*/
#define  MASTER_RD_BYTE_NACK         0x58   /*Master receive data without ack*/
#define  SLAVE_ADD_RCVD_RD_REQ          0xA8   /*It means slave address received with read request */
#define  SLAVE_ADD_RCVD_WR_REQ          0x60   /*It means slave address received with write request */
#define  SLAVE_DATA_RCVD        0x80   /*it means slave has received data*/
#define  SLAVE_BYTE_TRANSMITTED          0xB8   /*it means the data byte requested is transmitted*/


#define  STATUS_BITS_MASK	0b11111000

#define DIVISION_BY_ONE     0u
#define DIVISION_BY_FOUR    1u
#define DIVISION_BY_16      2u
#define DIVISION_BY_64      3u



#endif
