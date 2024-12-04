NAME         = main.hex
SRC          = main.c
OBJ          = main.bin
CC           = avr-gcc
COPY         = avr-objcopy
RM           = rm -f
FLAGS        = -O2
MMCU         = -mmcu=atmega328p
F_CPU        = -F_CPU=16000000UL
BAUD         = 115200
PROGRAMMER   = arduino
PORT         = /dev/ttyUSB0

all: hex flash

hex:
	$(CC) $(MMCU) $(F_CPU) $(FLAGS) -o $(OBJ) $(SRC)
	$(COPY) $(OBJ) $(NAME)

flash: 
	avrdude -p m328p -b $(BAUD) -c $(PROGRAMMER) -P $(PORT) -D -U $(NAME)

clean:
	$(RM) $(OBJ) $(NAME)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re