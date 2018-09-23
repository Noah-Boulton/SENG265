CC=gcc
CFLAGS=-I.
DEPS = hello.h
OBJ = helloworld.o hello.o 

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

helloworld: $(OBJ)
		gcc -o bin/$@ $^ $(CFLAGS)
