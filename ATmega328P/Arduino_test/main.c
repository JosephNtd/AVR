#define __AVR_ATmega328P__ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>


int main(void) {
    DDRD |=   (1 << 6) | (1 << 7);
    DDRD &= ~ (1 << 2) | (1 << 3);
    PORTD |=  (1 << 2) | (1 << 3);
    while (1) {
        if((PIND & (1 << 2))==0){
            PORTD ^= (1 << 6);
            while((PIND & (1 << 2))==0);
        } 
        else if ((PIND & (1 << 3))==0)
        {
            PORTD ^= (1 << 7);
            while((PIND & (1 << 3))==0);
        }       
    }
    return 0;
} 