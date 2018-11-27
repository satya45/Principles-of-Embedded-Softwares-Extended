# _*_ MakeFile _*_

CC = gcc

CFLAGS = -Wall\
	-DUNIT_TEST\
	-I../inc/
CUNIT = -lcunit

vpath %.c ../src

SRC := circbuff.c test_circbuff_random.c

OBJ := $(SRC:.c=.o)

unittest: $(OBJ)
	$(CC) -o unittest $(OBJ) $(CFLAGS) $(CUNIT)

clean:
	rm -f *.o unittest 
