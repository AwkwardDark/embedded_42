#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define UART_BAUDRATE 115200  // Bit rate


// Function to transmit a character via UART
void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); // Wait for transmit buffer to be empty
    UDR0 = c;					  	// Send the character
}

// Function to initialize UART
void uart_init(void)
{
    uint16_t ubrr;

    ubrr = F_CPU / ((16 * UART_BAUDRATE) - 1); // Calculate baud rate register value
    UBRR0H = ubrr >> 8;                      // Set high byte of baud rate
    UBRR0L = ubrr;                           // Set low byte of baud rate
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0); // USART transmitter, receiver and receiver interrupt enable
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);  // Set frame format: 8 data bits, no parity, 1 stop bit
	SREG |= (1 << 7); //Autorizes global interruptions
}

ISR(USART_RX_vect)
{
    char c = UDR0;
	
	if (c >= 'a' && c <= 'z')
		c -= 32;
	else if (c >= 'A' && c <= 'Z')
		c += 32;
	uart_tx(c);
}

int main(void)
{
    uart_init();  // Initialize UART

    while (1){}
    return (0);
}