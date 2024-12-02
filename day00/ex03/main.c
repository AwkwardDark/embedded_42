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
	DDRB = (1 << 0);
	// Sets PD2 (SW1) to input
	DDRD = (0 << 2);
	while (1)
	{
		// If pressed led turns on
		if (!(PIND & (1 << 2)))
		{
			flag = ft_change_state(flag);
			while (!(PIND & (1 << 2)));
		}
		if (flag == 1)
			PORTB = (1 << 0);
		if (flag == 0)
			PORTB = (0 << 0);
		_delay_ms(100);
	}
	return (0);
}
