#define __AVR_ATmega328P__ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>

int main(void) { 
    DDRD &= ~(1 << 3);
    PORTD |= (1 << 3);
    EICRA |=  (1 << ISC11 );
    EIMSK |=  (1 << INT1  );
    sei();
    while(1) {   
        
    }
}

ISR(INT1_vect)
{
    PORTD ^= (1 << PD7);
    while(!(PORTD & (1<<PD3)));
}
