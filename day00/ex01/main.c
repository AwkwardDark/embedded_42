#include <avr/io.h>

int main (void)
{
    DDRB = (1 << 0x0000);
    while(1)
    {
        PORTB = (1 << 0x0000);
    }
    return(0);
}
