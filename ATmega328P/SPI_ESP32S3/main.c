#define __AVR_ATmega328P__ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define Led1 PD6
#define Led2 PD7

#define MOSI PB3
#define MISO PB4
#define SCK PB5
#define SS PB2

volatile uint8_t recv_data;

void Slave_Init(void){
    DDRB |=   (1<<MISO);
    DDRB &= ~ (1<<MOSI) | (1<<SS) | (1<<SCK);
    SPCR |=   (1<<SPIE) | (1<<SPE);
}

int main() {
    DDRD |= (1<<Led1) | (1<<Led2);
    Slave_Init();
    sei();
    while (1) {
    }
    return 0;
}

ISR(SPI_STC_vect){
    while (!(SPSR & (1<<SPIF)));
    recv_data = SPDR;
    if (recv_data == 'A') {
        PORTD ^= (1<<Led1);
    }
    if (recv_data == 'B') {
        PORTD ^= (1<<Led2);
    }
    _delay_ms(100);
}