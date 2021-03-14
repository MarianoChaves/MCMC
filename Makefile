# Config

local_GSLFLAGS:=$(gsl-config --libs)
local_GSFLAGS:=$(gsl-config --cflags)

# --Make File--

CC = g++
C_FLAGS = -Wall -g -std=c++11
GSL_FLAGS= -lgsl -lgslcblas 


CC_SOURCE = $(wildcard src/*.cpp)
H_SOURCE = $(wildcard src/*.h)

FILE = $(subst src/, , $(CC_SOURCE))

BIN = $(addprefix src/bin/,$(FILE:.cpp=.o))


all: bin uti
	
bin: $(BIN)
src/bin/%.o: src/%.cpp src/%.h
	$(CC) $(C_FLAGS) -o $@ -c $< $(GSL_FLAGS)


uti: test.cpp $(H_SOURCE) $(CC_SOURCE) $(BIN)
	$(CC) $(C_FLAGS) -o test $< $(BIN) $(GSL_FLAGS)

clean:
	rm -f $(BIN) test.o
