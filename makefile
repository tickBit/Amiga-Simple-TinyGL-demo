CC=gcc
CFLAGS=-O2 -fomit-frame-pointer -m68020

all: TinyGL-demo
 
TinyGL-demo: TinyGL-demo.o
	$(CC) $(LFLAGS) -o $@ $< -lTinyGL -lamiga -lm

TinyGL-demo.o: TinyGL-demo.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o
