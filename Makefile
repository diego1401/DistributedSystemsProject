CXX = g++
CFLAGS = -lpthread -std=c++17 -Wall

SOURCES = main.cpp 
OBJECTS = main.o 


exec:
	$(CXX) $(CFLAGS) main.cpp -o exec

clean:
	rm exec
