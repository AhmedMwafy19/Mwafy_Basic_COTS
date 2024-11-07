#ifndef SPI_CFG_H
#define SPI_CFG_H
/*Configure whether This module will work as Master or Slave 1)SPI_MASTER
 * 															 2)SPI_SLAVE*/
#define SPI_MODE    SPI_MASTER
/*Configure The Order in which data is transferred 1)SPI_LSB_FIRST
 * 												   2)SPI_MSB_FIRST*/
#define SPI_DATA_ORDER SPI_MSB_FIRST
/*Configure SPI Clock Rate 1)MC_RATE_DIVIDED_BY_4
 * 						   2)MC_RATE_DIVIDED_BY_16
 * 						   3)MC_RATE_DIVIDED_BY_64
 * 						   4)MC_RATE_DIVIDED_BY_128*/
#define SPI_CLOCK_RATE   MC_RATE_DIVIDED_BY_128

/*If you want to double the rate write 1u if not 0u*/
#define SPI_RATE_DOUBLING  0u
#endif
