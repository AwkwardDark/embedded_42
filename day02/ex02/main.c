#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define UART_BAUDRATE 115200  // Bit rate

// Function to transmit a character via UART
void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); // Wait for transmit buffer to be empty
    UDR0 = c;						  // Send the character
}

// Function to receive a character via UART
char uart_rx(void)
{
	while (!(UCSR0A & (1 << RXC0))); // Wait to receive a bit
	return (UDR0);
}


// Function to initialize UART
void uart_init(void)
{
    unsigned int ubrr;

    ubrr = F_CPU / ((16 * UART_BAUDRATE) - 1); // Calculate baud rate register value
    UBRR0H = ubrr >> 8;                      // Set high byte of baud rate
    UBRR0L = ubrr;                           // Set low byte of baud rate
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);    // Enable transmiter and receiver
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // Set frame format: 8 data bits, no parity, 1 stop bit
}

int main(void)
{
    char	c;

	uart_init();  // Initialize UART
    while (1)
	{
		c = uart_rx();
		uart_tx(c);
	}
    return (0);
}
