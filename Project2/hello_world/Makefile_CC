PLATFORM=HOST
vpath %.c src/
TARGET= MAIN
LINKER_FILE= MKL25Z128xxx4_flash.ld
INCLUDES_COMMON= -I inc/

ifeq	($(PLATFORM),HOST)
	CC = gcc
	FLAGS= -D$(TARGET)
	LDFLAGS = -Wl,-Map=$(TARGET).map
	SRC := circbuff.c main.c
	OBJ := $(SRC:.c=.o)
	CFLAGS = -Wall -g -O0 -std=c99 $(INCLUDES_COMMON)
	CPPFLAGS=
endif

ifeq	($(PLATFORM),KL25Z)
	CC=arm-none-eabi-gcc
	INCLUDES_KL25Z= $(INCLUDES_COMMON) -I kl25z/
	SRC := circbuff.c main.c system_MKL25Z4.c
	#SSRC := startup_MKL25Z4.S
	CFLAGS = -Wall -g -O0 -std=c99
	FLAGS= -mthumb -mcpu=cortex-m0plus -march=armv6-m -mfloat-abi=soft -mfpu=fpv4-sp-d16 -specs=nosys.specs $(INCLUDES_KL25Z)
	LDFLAGS = -Wl,-T $(LINKER_FILE)
	CPPFLAGS = -DKL25Z -DMAIN
	OBJ := $(SRC:.c=.o) startup_MKL25Z4.o
endif

ifeq	($(PLATFORM),BBB)
	CC=arm-linux-gnueabihf-gcc
	CFLAGS= -Wall -g -O0 -std=c99 $(INCLUDES_COMMON)
	FLAGS= -DBBB -DMAIN -D VERBOSE
	LDFLAGS = -Wl
	SRC := circbuff.c main.c
	OBJ := $(SRC:.c=.o)
	CPPFLAGS=

endif

%.o : %.c
	-@echo 'Creating object files'
	$(CC) $(CFLAGS) $(FLAGS) $(CPPFLAGS) -c $< -o $@

%.asm : %.c
	-@echo 'Creating Assembly files'
	$(CC) $(CFLAGS) $(FLAGS) $(CPPFLAGS)-S $< -o $@
%.i : %.c
	-@echo 'Creating preprocessing files'
	$(CC) $(CFLAGS) $(FLAGS) $(CPPFLAGS) -E $< -o $@

build: 	$(OBJ)
	$(CC) $(CFLAGS) $(FLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJ) -o $(TARGET).elf	

	
clean:
	rm -f *.o *.elf *.map *.i
