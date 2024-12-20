#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL
#define UART_BAUDRATE 115200 // Bit rate

// Function to transmit a character via UART
void uart_tx(char c)
{
	while (!(UCSR0A & (1 << UDRE0)))
		;	  // Wait for transmit buffer to be empty
	UDR0 = c; // Send the character
}

char uart_rx(void)
{
	while (!(UCSR0A & (1 << RXC0)))
		; // Wait to receive a bit
	return (UDR0);
}

// Function to print a string
void uart_printstr(const char *str)
{
	for (int i = 0; str[i] != 0; i++)
		uart_tx(str[i]);
}

// Function to initialize UART
void uart_init(void)
{
	unsigned int ubrr;

	ubrr = F_CPU / ((16 * UART_BAUDRATE) - 1); // Calculate baud rate register value
	UBRR0H = ubrr >> 8;						   // Set high byte of baud rate
	UBRR0L = ubrr;							   // Set low byte of baud rate
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);	   // Enable transmitter
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);   // Set frame format: 8 data bits, no parity, 1 stop bit
}

int ft_strcmp(unsigned char *str1, unsigned char *str2)
{
	int i = 0;

	while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0')
		i++;
	return (str1[i] - str2[i]);
}

void led_party(void)
{
	int	i = 0;
	
	while (i++ < 5)
	{
		PORTB = (1 << PB0); 			  							 //  9= 0b000000001
		_delay_ms(1500);
		PORTB ^= (1 << PB0) | (1 << PB1); // -> 0b000000001 ^ 0b00000011 = 0b000000010
		_delay_ms(1500);
		PORTB ^= (1 << PB1) | (1 << PB2); // -> 0b000000010 ^ 0b00000110 = 0b000000100
		_delay_ms(1500);
		PORTB ^= (1 << PB2) | (1 << PB4); // -> 0b000000100 ^ 0b00010100 = 0b000010000
		_delay_ms(1500);
		PORTB ^= (1 << PB4) | (1 << PB2); // -> 0b000000010 ^ 0b00000110 = 0b000000100
		_delay_ms(1500);
		PORTB ^= (1 << PB2) | (1 << PB1); // -> 0b000000001 ^ 0b00000011 = 0b000000010
		_delay_ms(1500);
	}
}

int main(void)
{
	unsigned char username[127];
	unsigned char password[127];
	int i = 0;
	int j = 0;
	unsigned char c;

	uart_init();

	// setting LEDs
	DDRB |= 1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4;
	PORTB &= ~(1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4);
	while (1)
	{
		uart_printstr("Enter your login:\r\n\tusername: ");
		while (i < 127)
		{
			c = uart_rx();
			if (c == '\r')
				break;
			if (c == 127 && i > 0)
			{
				username[--i] = '\0';
				uart_printstr("\b \b");
				j--;
			}
			else if (c != 127)
			{
				username[i] = c;
				uart_tx(c);
				i++;
				j = i + 1;
			}
		}
		username[i] = '\0';
		i = 0;
		c = 0;
		uart_printstr("\r\n\tpassword: ");
		while (i < 127)
		{
			c = uart_rx();
			if (c == '\r')
				break;
			if (c == 127 && j > i)
			{
				password[--i] = '\0';
				uart_printstr("\b \b");
				j--;
			}
			else if (c != 127)
			{
				password[i] = c;
				c = '*';
				uart_tx(c);
				i++;
				j = i + 1;
			}
		}
		password[i] = '\0';
		if (!ft_strcmp(username, "totoro") && !ft_strcmp(password, "123456"))
		{
			uart_printstr("\r\nWelcome Totoro :)!\r\n\r\n");
			led_party();
			PORTB &= ~(1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB4);
		}
		else
			uart_printstr("\r\nBad username or password :(, try again\r\n\r\n");
	}

	return (0);
}
