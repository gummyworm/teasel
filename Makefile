LIBS  = -L. -levo2
INCLUDES = -I../evo2
CFLAGS = -Wall

SRC = $(wildcard *.c)
CSRC=$(wildcard components/*.c)

moor: $(SRC) $(CSRC)
	gcc -o $@ $^ $(CFLAGS) $(INCLUDES) $(LIBS)

clean:
	rm moor
