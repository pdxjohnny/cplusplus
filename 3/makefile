CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp gen.cpp employ.cpp
OBJECTS=$(SOURCES:.cpp=.o)
TEST_SOURCES=test.cpp gen.cpp
EXECUTABLE=a.out

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

test:
	$(CC) $(TEST_SOURCES)

clean:
	rm *.o a.out
