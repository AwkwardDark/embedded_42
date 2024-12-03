#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int value = 0;

	// Sets PB0, PB1, PB2 and PB4 to output
	DDRB |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 4); 
	// Sets PD2 (SW1) and PD3 (SW2) to input
	DDRD &= ~((1 << 2) | (1 << 4));
	while (1)
	{
		if (!(PIND & (1 << 2)) && value < 15)
		{
			value++;
			while (!(PIND & (1 << 2)));
		}
		if (!(PIND & (1 << 4)) && value > 0)
		{
			value--;
			while (!(PIND & (1 << 4)));
		}
		PORTB = ((value > 7) << 4) | (value & 7);
		_delay_ms(100);
	}
	return (0);
}
