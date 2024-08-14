// Default clock source is internal 8MHz RC oscillator
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

int main()
{
  DDRC |= (1 << 5);
  PORTC |= (1 << 5);
  while (1)
  {
  }
  return 0;
}