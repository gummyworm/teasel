LIBS  = -L. -levo2
INCLUDES = -I../evo2 -I.
CFLAGS = -Wall

SRC = $(wildcard *.c)
CSRC=$(wildcard components/*.c)
SYSRC=$(wildcard systems/*.c)
SCSRC=$(wildcard scenes/*.c)

teasel: $(SRC) $(CSRC) $(SYSRC) $(SCSRC)
	gcc -o $@ $^ $(CFLAGS) $(INCLUDES) $(LIBS)

clean:
	rm teasel 
