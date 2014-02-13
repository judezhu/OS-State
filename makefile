#makefile4
CC=g++
CFLAGS=-I.
OBJ = OS_state.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

OS_state: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f OS_state %.o
	
