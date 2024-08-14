# SPI
The Serial Peripheral Interface (SPI) allows high-speed synchronous data transfer between the ATmega328P and peripheral devices or between several AVR devices.

## SPI Pins Overrides

|Pin | Diretion, Master SPI| Direction, Slave SPI|
|----|---------------------|---------------------|
|MOSI| User Defined        | Input               |
|MISO| Input               | User defined        |
|SCK | User Defined        | Input               |
|SS  | User Defined        | Input               |

## Data Modes

There are four combinations of SCK phase and polarity with respect to serial data, which are determined by control bits CPHA and CPOL.

|                  |Leading Edge |Trailing Edge|SPI Mode|
|------------------|---------------|-----------------|--|
|CPOL = 0, CPHA = 0| Sample (Rising) | Setup(Falling) |0|
|CPOL = 0, CPHA = 1| Setup(Rising) | Sample (Falling) |1|
|CPOL = 1, CPHA = 0| Sample (Falling) | Setup(Rising) |2|
|CPOL = 1, CPHA = 1| Setup(Falling) | Sample (Rising) |3|

## Register Description
 
- ### **SPCR  – SPI Control Register**
 
  ![](doc/image.png)

  - `Bit 7 - SPIE. SPI Interrupt Enable:` This bit causes the SPI interrupt to be executed if SPIF bit in the SPSR Register is set and the if the global interrupt enable bit in SREG is set.

  - `Bit 6 – SPE`. SPI Enable: This bit **must be set** to enable any SPI operations.
  
  - `Bit 5 – DORD. Data Order: `
    - When the DORD bit is written to one, the LSB of the data word is transmitted first.
    - When the DORD bit is written to zero, the MSB of the data word is transmitted first
  - `Bit 4 – MSTR. Master/Slave Select:` This bit selects Master SPI mode when written to one, and Slave SPI mode when written logic zero. 
  - `Bit 3 – CPOL. Clock Polarity:`  When this bit is written to one, SCK is high when idle. When CPOL is written to zero, SCK is low when idle. 
     |CPOL| Leading Edge| Trailing Edge|
     |----|-------------|--------------|
     |0   | Rising      | Falling      |
     |1   | Falling     | Rising       |

  - `Bit 2 – CPHA. Clock Phase:` The settings of the clock phase bit (CPHA) determine if data is sampled on the leading (first) or trailing (last) edge of SCK.
     |CPHA| Leading Edge| Trailing Edge|
     |----|-------------|--------------|
     |0   | Sample      | Setup        |
     |1   | Setup       | Sample       |

  - `Bits 1, 0 – SPR1, SPR0. SPI Clock Rate Select 1 and 0:`  
    - These two bits control the SCK rate of the device configured as a Master. SPR1 and SPR0 have no effect on the Slave. The relationship between SCK and the Oscillator Clock frequency fosc is shown in the following table: 
      |SPI2X| SPR1| SPR0| SCK Freequency|
      |-----|-----|-----|---------------|
      |0    |0    |0    | f/4           | 
      |0    |0    |1    | f/16          |
      |0    |1    |0    | f/64          |
      |0    |1    |1    | f/128         |
      |1    |0    |0    | f/2           |
      |1    |0    |1    | f/8           |
      |1    |1    |0    | f/32          |
      |1    |1    |1    | f/64          |

- ### **SPSR – SPI Status Register**
 
  ![](doc/image-1.png)

    - `Bit 7 – SPIF. SPI Interrupt Flag:` When a serial transfer is complete, the SPIF Flag is set. An interrupt is generated if SPIE in SPCR is set and global interrupts are enabled. 
  
    - `Bit 6 – WCOL. Write COLlision Flag:` The WCOL bit is set if the SPI Data Register (SPDR) is written during a data transfer. The WCOL bit (and the SPIF bit) are cleared by first reading the SPI Status Register with WCOL set, and then accessing the SPI Data Register.
  
- ### **SPDR – SPI Data Register**

    ![](doc/image2.png)

     The SPI Data Register is a Read/Write Register used for data transfer between the Register File and the SPI Shift Register. Writing to the register initiates data transmission. Reading the register causes the Shift Register Receive buffer to be read.
