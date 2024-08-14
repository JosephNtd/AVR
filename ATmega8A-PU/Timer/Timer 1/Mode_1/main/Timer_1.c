#include <avr/io.h>
#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void)
{
	DDRC |= (1 << 5); //Set chan output cho led
	PORTC &= ~(1<<5); //Tat led

  TCCR1B |= (1 << WGM12)|(1<<CS11)|(1<<CS10);//Set prescale va mode (Mode 4)
	TCNT1 = 0; //BOTTOM, Dem tu 0 -> 65535. Co the tuy chinh
  TIMSK |= (1 << OCIE1A);//mặt nạ ngắt
  sei ();
  while (1) 
  {
  }
}

ISR (TIMER1_COMPA_vect)//Vector ngat COMPARE
{
	TCNT1 = 0; // Set lai gia tri dem cho bien
	PORTC ^= (1 << 5);//Chuyen doi trang thai cua led (Bat len)
}
		