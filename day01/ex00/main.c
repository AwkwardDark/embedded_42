#include <avr/io.h>

# define PB1 1

int main (void)
{
	DDRB |= (1 << PB1); //Setting led D2 (PB1) as output
	PORTB &= ~(1 << PB1); //Turning off led D2
    while(1)
    {
		//Creating a pause of 0.5s, led will blink at a frequence of 1Hz
		for (uint32_t i = 0; i < 240000; i++);
        //Using the bitwise XOR operation to toogle the state of the led
		PORTB = PORTB ^ (1 << PB1);
    }
    return(0);
}
