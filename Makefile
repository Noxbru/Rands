CC = gcc
CFLAGS = -O2 -march=native -flto
ERROR_FLAGS = -Wall -Wextra -pedantic -std=c11

CFLAGS += $(ERROR_FLAGS)

OBJ_RANDS = parisi.o \
			well.o

rands: $(OBJ_RANDS)
		ld -r $(OBJ_RANDS) -o rands.o

parisi.o: parisi.c
well.o: well.c

clean:
		@rm *.o
