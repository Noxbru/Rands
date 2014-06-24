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

OBJ_RANDS = src/isaac.o     \
			src/isaac_x64.o \
			src/parisi.o    \
			src/parisi_sse.o\
			src/mersenne.o  \
			src/well.o      \
			src/well_x64.o  \
			src/xorshift.o
OBJ_RANDS_FINAL = rands.o
#SOBJ_RANDS_FINAL= librands.so
LIB_RANDS_FINAL = librands.a

all: rands

rands: $(OBJ_RANDS_FINAL) $(LIB_RANDS_FINAL)
	@

$(OBJ_RANDS_FINAL): $(OBJ_RANDS)
	ld -r $(OBJ_RANDS) -o $(OBJ_RANDS_FINAL)

#$(SOBJ_RANDS_FINAL): $(OBJ_RANDS)
#$(CC) $(CFLAGS) -fPIC $(OBJ_RANDS) -o $(SOBJ_RANDS_FINAL) $(LDFLAGS) -shared

$(LIB_RANDS_FINAL): $(OBJ_RANDS)
	gcc-ar rcs $(LIB_RANDS_FINAL) $(OBJ_RANDS)

src/isaac.o: 		src/isaac.c
src/isaac_x64.o: 	src/isaac_x64.c
src/parisi.o: 		src/parisi.c
src/parisi_sse.o:	src/parisi_sse.c
src/mersenne.o: 	src/mersenne.c
src/well.o: 		src/well.c
src/well_x64.o: 	src/well_x64.c
src/xorshift.o: 	src/xorshift.c

speed-test: rands tests/speed.o
	$(CC) $(CFLAGS) tests/speed.o -o tests/speed $(LDFLAGS) -lrands -L.
	./tests/speed

speed.o: tests/speed.c



clean:
	@rm -f $(OBJ_RANDS)
	@rm -f $(OBJ_RANDS_FINAL)
#@rm -f $(SOBJ_RANDS_FINAL)
	@rm -f $(LIB_RANDS_FINAL)
