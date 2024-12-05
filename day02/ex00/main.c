#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define UART_BAUDRATE 115200  // Bit rate

ISR(TIMER1_COMPA_vect)
{
    uart_tx('Z');  // Transmit 'Z' via UART
}

// Function to transmit a character via UART
void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); // Wait for transmit buffer to be empty
    UDR0 = c;						  // Send the character
}

// Function to initialize UART
void uart_init(void)
{
    unsigned int ubrr;

    ubrr = F_CPU / ((16 * UART_BAUDRATE) - 1); // Calculate baud rate register value
    UBRR0H = ubrr >> 8;                      // Set high byte of baud rate
    UBRR0L = ubrr;                           // Set low byte of baud rate
    UCSR0B = (1 << TXEN0);                   // Enable transmitter
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // Set frame format: 8 data bits, no parity, 1 stop bit
}

// Function to initialize Timer1
void set_timer()
{
    SREG |= (1 << 7); //Autorizes global interruptions

    TCCR1B |= (1 << WGM12) | (1 << CS12); // CTC mode with OCR1A as TOP value + prescaler 256
    OCR1A = F_CPU / 256; // 1 Hz frequency
    TIMSK1 |= (1 << OCIE1A);
}

int main(void)
{
    uart_init();  // Initialize UART
    set_timer();  // Initialize Timer1


    while (1){}
    return (0);
}
