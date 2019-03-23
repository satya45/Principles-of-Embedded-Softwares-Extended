PLATFORM=BBG
vpath %.c src/
TARGET= project1
INCLUDES_COMMON= -I inc/

ifeq ($(PLATFORM),HOST)
	CC = gcc
	FLAGS= -D$(TARGET)
	LDFLAGS = -lpthread -lrt
	SRC := main.c logger.c temp.c light.c sockets.c gpio.c
	OBJ := $(SRC:.c=.o)
	CFLAGS = -g $(INCLUDES_COMMON)
endif

ifeq	($(PLATFORM),BBG)
	CC=arm-linux-gcc
	FLAGS= -D$(TARGET)
	LDFLAGS = -lpthread -lrt
	SRC := main.c logger.c temp.c light.c sockets.c gpio.c
	OBJ := $(SRC:.c=.o)
	CFLAGS = -g $(INCLUDES_COMMON)

endif


build: 	$(OBJ)
	$(CC) $(CFLAGS) $(FLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

	
clean:
	rm -f *.o *.elf *.map