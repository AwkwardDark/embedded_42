#include <avr/io.h>
#include <util/delay.h>

int ft_change_state(flag)
{
	if (flag)
		return (0);
	return (1);
}

int main(void)
{
	int flag = 0;

	// Sets PB0 to output
	DDRB = (1 << PB0);
	// Sets PD2 (SW1) to input
	DDRD &= ~(1 << PD2);
	while (1)
	{
		// If pressed led turns on
		if (!(PIND & (1 << PD2)))
		{
			flag = ft_change_state(flag);
			while (!(PIND & (1 << PD2)));
		}
		if (flag)
			PORTB |= (1 << 0);//Turns on led D1
		else
			PORTB &= ~(1 << 0);//Turns off led D1
		_delay_ms(100);
	}
	return (0);
}
