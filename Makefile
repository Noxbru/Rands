CC = gcc
CFLAGS = -O2 -march=native -flto
ERROR_FLAGS = -Wall -Wextra -pedantic -std=gnu11
LDFLAGS = -lm -lrt

ifeq ($(CC),gcc)
	GCC_VERSION = $(shell gcc -dumpversion | sed 's/\.//g')
	GCC_GT_480  = $(shell expr $(GCC_VERSION) \>= 480)

	ifeq ($(GCC_GT_480),1)
		ERROR_FLAGS += -fno-diagnostics-show-caret
	endif
endif

CFLAGS += $(ERROR_FLAGS)

OBJ_RANDS = isaac.o	    \
			isaac_x64.o \
			parisi.o    \
			parisi_sse.o\
			mersenne.o  \
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
mersenne.o: mersenne.c
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
