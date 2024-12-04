#include <avr/io.h>

# define F_CPU 16000000UL

/* TCCR: TIMER/COUNTER CONTROL REGISTER
* COMAx's defines OCx behaviour: OC1A switches on TOP
* WGMx defines which top value to use: 15
* CSx defines the clock prescaler  clkio/256 */
int	main(void)
{
	DDRB |= (1 << PB1);	//Set led D2 as output
	TCCR1A = 0;
	TCCR1B = 0;
	/*COM1A1 COM1A0 . . . . WGM11 WGM10*/
	TCCR1A |= (1 << COM1A0) | (1 << WGM10) | (1 << WGM11);
	/*WGM13 WGM12 CS12 CS11 CS10*/
	TCCR1B |=  (1 << WGM12)| (1 << WGM13) | (1 << CS10) | (1 << CS12);
	/*TOP value: nb of cycle before OC1A increase*/
	OCR1A = F_CPU / (2 * 1 * 1024); //OCR1A = F_cpu / (2 * desired_frequence * prescaler)
	while (1){}
}
