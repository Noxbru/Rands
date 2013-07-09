CC = gcc
CFLAGS = -O2 -march=native -flto
ERROR_FLAGS = -Wall -Wextra -pedantic -std=gnu11 -fno-diagnostics-show-caret
LDFLAGS = -lm -lrt

CFLAGS += $(ERROR_FLAGS)

OBJ_RANDS = isaac.o	    \
			isaac_x64.o \
			parisi.o    \
			parisi_sse.o\
			well.o      \
			well_x64.o  \
			xorshift.o
OBJ_RANDS_FINAL = rands.o
LIB_RANDS_FINAL = librands.a

all: rands

rands: $(OBJ_RANDS)
	ld -r $(OBJ_RANDS) -o $(OBJ_RANDS_FINAL)
	ar rcs $(LIB_RANDS_FINAL) $(OBJ_RANDS)

isaac.o: isaac.c
isaac_x64.o: isaac_x64.c
parisi.o: parisi.c
parisi_sse.o: parisi_sse.c
well.o: well.c
well_x64.o: well_x64.c
xorshift.o: xorshift.c

speed-test: rands speed.o
	$(CC) $(CFLAGS) speed.o -o speed $(LDFLAGS) -lrands -L.
	./speed

speed.o: speed.c

clean:
	@rm *.o
	@rm $(LIB_RANDS_FINAL)
