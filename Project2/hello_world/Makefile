#----*CUSTOM MAKEFILE FOR FRDM KL25Z ON LINUX*----


PLATFORM=KL25Z
vpath %.c src/
TARGET= MAIN
LINKER_FILE= MKL25Z128xxx4_flash.ld
INCLUDES_COMMON= -I inc/
CP   = arm-none-eabi-objcopy
AS   = gcc -x assembler-with-cpp
HEX  = $(CP) -O ihex
BIN  = $(CP) -O binary -S



ifeq	($(PLATFORM),KL25Z)
	CC=arm-none-eabi-gcc
	EXE:=main.axf
	INCLUDES_KL25Z= $(INCLUDES_COMMON) -I kl25z/
	SRC := main.c system_MKL25Z4.c uart.c
	#SSRC := startup_MKL25Z4.S
	CFLAGS =-g -O0 -gdwarf-2 -mthumb -fomit-frame-pointer -Wall -Wstrict-prototypes -fverbose-asm -Wa,-ahlms=$(<:.c=.lst) 
	FLAGS= -mthumb -mcpu=cortex-m0plus -march=armv6-m -mfloat-abi=soft -mfpu=fpv4-sp-d16 -specs=nosys.specs $(INCLUDES_KL25Z)
	LDFLAGS = -Wl,-T $(LINKER_FILE) -o $(EXE)
	CPPFLAGS = -DKL25Z -DMAIN
	OBJ := $(SRC:.c=.o) startup_MKL25Z4.o
srec: $(TARGET).srec
bin: $(TARGET).bin
hex: $(TARGET).hex
	
endif

%.o : %.c
	-@echo 'Creating object files'
	$(CC) $(CFLAGS) $(FLAGS) $(CPPFLAGS) -c $< -o $@ -lm

%.asm : %.c
	-@echo 'Creating Assembly files'
	$(CC) $(CFLAGS) $(FLAGS) $(CPPFLAGS)-S $< -o $@
%.i : %.c
	-@echo 'Creating preprocessing files'
	$(CC) $(CFLAGS) $(FLAGS) $(CPPFLAGS) -E $< -o $@
	

$(TARGET).elf: 	$(OBJ)
	$(CC) $(CFLAGS) $(FLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJ) -o $@

%.srec: %.elf
	$(CP) -O srec $< $@

%hex: %.elf
	$(CP) -O hex $< $@
%bin: %.elf
	$(CP) -O bin -S $< $@
clean:
	rm -f *.o *.elf *.map *.i *.srec
