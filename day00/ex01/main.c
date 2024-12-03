#include <avr/io.h>

int main (void)
{
    //Setting PB0 led as output
	DDRB |= (1 << PB0);
    while(1)
    {
        //Turning it on, PORTB is 0000 0000 by default, now is 0000 0001
		PORTB |= (1 << PB0);
    }
    return(0);
}
