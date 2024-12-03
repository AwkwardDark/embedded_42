#include <avr/io.h>
#include <util/delay.h>

int main (void)
{
    //Sets PB0 to output
	DDRB = (1 << 0);
    //Sets PD2 to input
	DDRD = (0 << 2);    
    while (1)
	{
        //If pressed turns on PB0
		if (!(PIND & (1 << 2)))
            PORTB = (1 << 0);
        PORTB = (0 << 0); //If not pressed PB0 is turned off
    }
    return (0);
}
