CC=g++
CFLAGS=-c -Wall -DARRAY=1
LDFLAGS=
SOURCES=main.cpp general.cpp user.cpp weather.cpp forecast.cpp forecast_dlist.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=homework

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o homework
