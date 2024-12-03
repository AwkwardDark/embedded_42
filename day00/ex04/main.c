#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	int value = 0;

	// Sets PB0 to output
	DDRB = (1 << 0);
	// Sets PB1 to output
	DDRB = (1 << 1);
	// Sets PB2 to output
	DDRB = (1 << 2);
	// Sets PB3 to output
	DDRB = (1 << 4);

	// Sets PD2 (SW1) to input
	DDRD = (0 << 2);
	// Sets PD3 (SW2) to input
	DDRD = (0 << 4);

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
		PORTB = ((value > 7) << 4) | (value & 0x0F);
		_delay_ms(100);
	}
	return (0);
}
