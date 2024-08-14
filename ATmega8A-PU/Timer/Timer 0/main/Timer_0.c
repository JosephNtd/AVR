#include <avr/io.h>
#define F_CPU 8000000UL
#include <avr/interrupt.h>
#include <util/delay.h>

void KhaiBao()
{
	DDRC |= (1 << 5); // Set chan output cho led
	PORTC &= ~(1<<5); //Tat led

  TCCR0 |= (1 << CS02); //Set prescale theo Bang 2
  /*Bien dem. (BOTTOM) Tu 0->255
  Ban co the dieu chinh 
  Vi du: TCNT0 = 100; 
  Thi se chay tu 100 -> 255
  */
	TCNT0 = 0; 
	
  TIMSK |= (1 << TOIE1);// Cho phep ngat tran nhu bang 3
  sei ();
}

int main(void)
{
	KhaiBao();
  while (1) 
  {
  }
}

ISR (TIMER0_OVF_vect)//Vector ngat tran 
{
	TCNT0 = 0; // Set lai gia tri dem cho bien, dua theo bien dem phia tren
	PORTC ^= (1 << 5); //chuyen doi trang thai cua led
}
