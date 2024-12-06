#include <avr/interrupt.h>
#include <avr/io.h>

#define TIMER1_PRESCALER 1024
#define F_CPU 16000000UL

#define BLUE  3
#define RED   5
#define GREEN 6

ISR(TIMER1_COMPA_vect)
{
	static uint8_t	rgb_color = RED;

	PORTD = 0;
	PORTD |= (1 << rgb_color);
	if (rgb_color == GREEN)
		rgb_color = BLUE;
	else if (rgb_color == BLUE)
		rgb_color = RED;
	else if (rgb_color == RED)
		rgb_color = GREEN;
}

int	main(void)
{
	SREG |= (1 << 7); // authorize the global interrupt
	DDRD |= (1 << PD6) | (1 << PD5) | (1 << PD3); // We set RGB led D5 as output
	TCCR1B |= (1 << WGM12) | (1 << CS12) | (1 << CS10); // CTC mode && prescaler set to 1024
	TIMSK1 |= (1 << OCIE1A); //To handle interrupt cycle
	OCR1A = F_CPU / TIMER1_PRESCALER;
	while (1){}
}
