#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
    //Sets PB0 to output
	DDRB |= (1 << PB0);
    //Sets PD2 to input
	DDRD &= ~(1 << PD2); 
    while (1)
	{
		if (!(PIND & (1 << PD2)))
            PORTB |= (1 << PB0); //If pressed turns on PB0
		else
	        PORTB &= ~(1 << PB0); //If not pressed PB0 is turned off
    }
    return (0);
}
