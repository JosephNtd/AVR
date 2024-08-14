#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>

volatile unsigned char recv_data;

int main(void)
{
	UBRRL = 51; 
	UCSRB |= (1 << RXEN) | (1 << RXCIE); 
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1); 
	sei();
	DDRC |= (1 << 5);
	PORTC |= (1 << 5);
	while (1)
	{			
	}
}
ISR(USART_RXC_vect)
{
	recv_data = UDR;
	if (recv_data == '1'){
		PORTC |= (1<<5);
	}
	if (recv_data == '2'){
		PORTC &= ~(1<<5);
	}
}