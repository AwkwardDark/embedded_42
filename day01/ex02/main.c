#include <avr/io.h>

# define F_CPU 16000000UL

/* DAY01 EX02 */
/* TCCR: TIMER/COUNTER CONTROL REGISTER
* COMAx's defines OCx behaviour: OC1A switches on TOP
* WGMx defines which top value to use: 14
* CSx defines the clock prescaler  clkio/1024 */
int	main(void)
{
	DDRB |= (1 << PB1);	//Set led D2 as output
	TCCR1A = 0;
	TCCR1B = 0;
	/*COM1A1 COM1A0 . . . . WGM11 WGM10*/
	TCCR1A |= (1 << COM1A1) | (1 << WGM11);
	/*WGM13 WGM12 CS12 CS11 CS10*/
	TCCR1B |=  (1 << WGM13) | (1 << CS10) | (1 << CS12);
	/*TOP value: nb of cycle before OC1A increase*/
	ICR1 = F_CPU / (2 * 1 * 1024); //ICR1 = F_cpu / (2 * desired_frequence * prescaler)
	OCR1A = ICR1 / 10;
	while (1){}
}