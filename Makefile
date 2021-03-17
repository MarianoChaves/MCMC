# Config

local_GSLFLAGS:=$(gsl-config --libs)
local_GSFLAGS:=$(gsl-config --cflags)

# --Make File--

CC = g++
C_FLAGS = -Wall -g -std=c++11
GSL_FLAGS= -lgsl -lgslcblas 


CC_SOURCE = $(wildcard src/*.cpp)
H_SOURCE = $(wildcard src/*.h) nu.h

FILE = $(subst src/, , $(CC_SOURCE))

BIN = $(addprefix src/bin/,$(FILE:.cpp=.o))


all: bin uti
	mv libnu.so /usr/lib/$(LIB_NAME)
	
bin: $(BIN)
src/bin/%.o: src/%.cpp src/%.h
	$(CC) $(C_FLAGS) -fPIC -o $@ -c $< $(GSL_FLAGS)


uti: libnu.so 
libnu.so: $(CC_SOURCE) $(H_SOURCE)
	$(CC) $(C_FLAGS) -fPIC -shared -o $@ $(CC_SOURCE) $(GSL_FLAGS) -lc

clean:
	rm -f $(BIN) libnu.so
