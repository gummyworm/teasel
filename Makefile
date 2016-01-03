LIBS  = -levo2
CFLAGS = -Wall

SRC=$(wildcard *.c)

moor: $(SRC)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm moor
