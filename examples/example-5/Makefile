# --Make File--

CC = g++
C_FLAGS = -Wall -g -std=c++11 -fopenmp



all: bin example
	
bin: $(BIN)
%.o: %.cpp %.h
	$(CC) $(C_FLAGS) -o $@ -c $<


example: example.cpp
	$(CC) $(C_FLAGS) -o $@ example.cpp -lnu

clean:
	rm -f $(BIN) example