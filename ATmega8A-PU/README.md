# AVR Programming with VSCode in Linux

## I. Install & Setup Environment

### 1. Install AVR-GCC Compiler & AVRDUDE
```sh
    sudo apt-get install gcc build-essential
    sudo apt-get install gcc-avr binutils-avr avr-libc gdb-avr
    sudo apt-get install libusb-dev
    sudo apt-get install avrdude
```
## 2. Build the program
Go in to the Makefile
- change the Program name
- change the Src Name
 ```sh
make
```
## 3. Upload the Program to Atmega8A
To ensure that the USBasp programmer is detected and connected to Atmega8A, verify the device signature:

    avrdude -c usbasp-clone -p m8

Upload the program:
Use the `Makefile` and execute this command:

    make upload
    
## II. Q&A 
 ### If VSCode did not understand #include or DDRC | PORT 
 Go to Extension -> Setting -> 
 - Include Path -> usr/lib/avr/include
 - Define -> add in main.c `#define __AVR_ATmega8A__`