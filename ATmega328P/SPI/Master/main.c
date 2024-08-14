#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>

int main(void){
    DDRD &= ~ (1 << PD2   );
    DDRD |=   (1 << PD6   ); 
    EICRA |=  (1 << ISC11 );
    EIMSK |=  (1 << INT1  );
    sei();
    while(1){
    }
    return (0);
}
ISR (INT1_vect){   
	PORTB ^= (1 << PD6); 
}
