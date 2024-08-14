/*
 * Intertupt(Ngat_Ngoai).cpp
 *
 * Created: 3/19/2024 2:58:55 PM
 * Author : Nguyen Tan Dat
 */ 
#define __AVR_ATmega8A__
#include <avr/io.h>
#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <util/delay.h>

#define Led_Default PC5
#define Led1 PB1
#define Led2 PB2

#define Button1 PD2
#define Button2 PD3

void KhaiBao()
{
	DDRB |= (1 << Led1) | (1 << Led2);
	DDRC |= (1 << Led_Default);
	DDRD &= ~(1 << Button1) | (1 << Button2);
	PORTD |= (1 << Button1) | (1 << Button2);
	
	MCUCR |= (1 << ISC11) | (1 << ISC01);
	GICR |= (1 << INT0) | (1 << INT1);
	sei();
}

int main(void)
{
	KhaiBao();
    
    while (1) 
    {
		PORTC |= (1 << Led_Default);
    }
}


ISR (INT0_vect)
{
	if ((PIND & (1 << Button1)) == 0)
	{
		PORTC &= ~ (1 << Led_Default);
		PORTB |= (1 << Led1);
		_delay_ms(5000);
		PORTB &= ~(1 << Led1);
	}
}

ISR (INT1_vect)
{
	if((PIND & (1 << Button2)) == 0 )
	{
		PORTC &= ~ (1 << Led_Default);
		PORTB |= (1 << Led2);
		_delay_ms(5000);
		PORTB &= ~(1 << Led2);
	}
}