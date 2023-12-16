#ifndef SPI_PRIV_H_
#define SPI_PRIV_H_

#define SPCR *((volatile u8 *) 0x2D)
#define SPIE    7
#define SPE     6
#define DORD    5
#define MSTR    4
#define CPOL    3
#define CPHA    2
#define SPR1    1  
#define SPR0    0
#define SPSR *((volatile u8 *) 0x2E)
#define SPIF    7
#define WCOL    6
#define SPI2X   0
#define SPDR *((volatile u8 *) 0x2F)

//MODE
#define MASTER_MODE     0
#define SLAVE_MODE      1
//DATA Order
#define LSB_FIRST       0
#define MSB_FIRST       1
//CLOCK_POLARITY
#define RISING_LEADING  0
#define FALLING_LEADING 1
//Clock Phase
#define SAMPLE_LEADING  0
#define SETUP_LEADING   1
//clock rate
#define F_SYS_4         0
#define F_SYS_16        1
#define F_SYS_64        2
#define F_SYS_128       3
#define F_SYS_2         4
#define F_SYS_8         5
#define F_SYS_32        6

//SPI Interrupt Enable
#define SPI_INTERRUPT_DISABLE         0
#define SPI_INTERRUPT_ENABLE          1

#endif /* SPI_PRIV_H_ */
