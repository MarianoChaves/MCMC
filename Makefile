# --Make File--

CC = g++
C_FLAGS = -Wall -g -std=c++11 -fopenmp


CC_SOURCE = $(wildcard src/*.cpp)
H_SOURCE = $(wildcard src/*.h)

FILE = $(subst src/, , $(CC_SOURCE))
HFILE = $(subst src/, , $(H_SOURCE))

BIN = $(addprefix src/bin/,$(FILE:.cpp=.o))


all: bin uti
	mv libnu.so /usr/lib/$(LIB_NAME)
	cp src/nu.h /usr/local/include/nu.h
	cp src/walker.h /usr/local/include/walker.h	
	cp src/mcmc.h /usr/local/include/mcmc.h
	cp src/ensemble.h /usr/local/include/ensemble.h
		
bin: $(BIN)
src/bin/%.o: src/%.cpp src/%.h
	$(CC) $(C_FLAGS) -fPIC -o $@ -c $<


uti: libnu.so 
libnu.so: $(CC_SOURCE) $(H_SOURCE)
	$(CC) $(C_FLAGS) -fPIC -shared -o $@ $(CC_SOURCE)

clean:
	rm -f $(BIN) libnu.so
