CC = gcc

SRC = UART_transmit.c \
      ../protocol/crc.c \
      ../protocol/packet.c \
      ../protocol/packet_serialize.c

OUT = uart.exe

CFLAGS = -Wall -Wextra

all:
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)

clean:
	del $(OUT)