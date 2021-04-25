# --Make File--

CC = g++
C_FLAGS = -Wall -g -std=c++11 -fopenmp


CC_SOURCE = $(wildcard src/*.cpp)
H_SOURCE = $(wildcard src/*.h)

FILE = $(subst src/, , $(CC_SOURCE))

BIN = $(addprefix src/bin/,$(FILE:.cpp=.o))


all: bin uti
	mv libnu.so /usr/lib/$(LIB_NAME)
	
bin: $(BIN)
src/bin/%.o: src/%.cpp src/%.h
	$(CC) $(C_FLAGS) -fPIC -o $@ -c $<


uti: libnu.so 
libnu.so: $(CC_SOURCE) $(H_SOURCE)
	$(CC) $(C_FLAGS) -fPIC -shared -o $@ $(CC_SOURCE)

clean:
	rm -f $(BIN) libnu.so
