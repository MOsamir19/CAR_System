
#ifndef SPI_SPI_PRIVATE_H_
#define SPI_SPI_PRIVATE_H_

/********************************************************************************************/
#define SPI_MASTER_MODE       1
#define SPI_SLAVE_MODE        2

/********************************************************************************************/
#define SPCR_REG   *((volatile u8 *)0x2D)
#define SPCR_SPR0        0
#define SPCR_SPR1        1
#define SPCR_MSTR        4
#define SPCR_DORD        5
#define SPCR_SPE         6
/********************************************************************************************/
#define SPDR_REG   *((volatile u8 *)0x2F)

/********************************************************************************************/
#define SPSR_REG   *((volatile u8 *)0x2E)
#define SPSR_SPIF        7
#define SPSR_SPI2X       0
/********************************************************************************************/
#endif /* SPI_SPI_PRIVATE_H_ */
