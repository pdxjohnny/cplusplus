CC=gcc
CFLAGS=-Wall -g -m32
LDFLAGS=-m32
SOURCES=gen.c cache.c hw5.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=hw5

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm *.o hw5 
