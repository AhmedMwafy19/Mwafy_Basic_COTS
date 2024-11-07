#ifndef SPI_REG_H
#define SPI_REG_H


#define   SPCR  *((volatile uint8 *)0x2D)  /*SPI Control Register*/
#define SPCR_SPIE   7u  /*SPI Interrupt enable*/
#define SPCR_SPE   6u  /*SPI enable*/
#define SPCR_DORD  5u  /*Data order*/
#define SPCR_MSTR  4u  /*Master slave select*/
#define SPCR_CPOL  3u  /*Clock Polarity*/
#define SPCR_CPHA  2u  /*Clock Phase*/
#define SPCR_SPR1  1u  /*Clock Rate select 1*/
#define SPCR_SPR0  0u  /*Clock Rate select 0*/


#define   SPSR  *((volatile uint8 *)0x2E)  /*SPI Status Register*/
#define SPSR_SPIF   7u  /*SPI Interrupt Flag*/
#define SPSR_WCOL   6u  /*Write Collision Flag*/
#define SPSR_SPI2X  0u  /*Double SPI CLK Rate */

#define   SPDR  *((volatile uint8 *)0x2F)  /*SPI Data Register */

#endif
