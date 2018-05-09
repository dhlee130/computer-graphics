HEADERS = vec.hpp mat.hpp operator.hpp transform.hpp
SOURCES = main.cpp
CC = g++
CFLAGS = -std=c++11
EXECUTABLE = 20143085
RM = rm -rf

all: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES)  -lGL -lGLU -lglut -lGLEW

clean:
	$(RM) *.o $(EXECUTABLE)
