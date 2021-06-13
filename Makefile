CXX = g++
CFLAGS = -O3 -lpthread -std=c++17 -Wall -lmetis

SOURCES = main.cpp 
OBJECTS = main.o 


exec:
	$(CXX) $(CFLAGS) main.cpp -o exec

clean:
	rm exec
