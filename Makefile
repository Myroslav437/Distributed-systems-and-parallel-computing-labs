all: compile clean

compile: mpoint.o
	g++ mpoint.o -o mpoint

mpoint.o: mpoint.cpp
	g++ -std=c++17 -c mpoint.cpp

clean:
	rm -rf *.o