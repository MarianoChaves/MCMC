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


example: example.cpp
	$(CC) $(C_FLAGS) -o $@ example.cpp $(GSL_FLAGS) -lnu



clean:
	rm -f $(BIN) test.o