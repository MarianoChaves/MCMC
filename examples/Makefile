# Config

local_GSLFLAGS:=$(gsl-config --libs)
local_GSFLAGS:=$(gsl-config --cflags)

# --Make File--

CC = g++
C_FLAGS = -Wall -g -std=c++11
GSL_FLAGS= -lgsl -lgslcblas 



all: bin example
	
bin: $(BIN)
%.o: %.cpp %.h
	$(CC) $(C_FLAGS) -o $@ -c $< $(GSL_FLAGS)


example: tests.cpp
	$(CC) $(C_FLAGS) -o $@ tests.cpp $(GSL_FLAGS) -lnu



clean:
	rm -f $(BIN) tests.o
