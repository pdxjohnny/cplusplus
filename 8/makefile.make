CC=g++
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.cpp general.cpp student.cpp course.cpp task.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=assignment3

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o assignment3
