CC = gcc
CFLAGS = -O2 -march=native -flto
ERROR_FLAGS = -Wall -Wextra -pedantic -std=c11

CFLAGS += $(ERROR_FLAGS)

OBJ_RANDS = parisi.o   \
			well.o     \
			well_x64.o
OBJ_RANDS_FINAL = rands.o
LIB_RANDS_FINAL = librands.a

rands: $(OBJ_RANDS)
		ld -r $(OBJ_RANDS) -o $(OBJ_RANDS_FINAL)
		ar rcs $(LIB_RANDS_FINAL) $(OBJ_RANDS)

parisi.o: parisi.c
well.o: well.c
well_x64.o: well_x64.c

clean:
		@rm *.o
		@rm $(LIB_RANDS_FINAL)
