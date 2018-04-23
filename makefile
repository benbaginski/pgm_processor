CXX=g++
CXXFLAGS= -std=c++11 -Ofast -Wall

all: pgm_reader

pgm_reader: main.o pgm_image.o
	${CXX} ${CXXFLAGS} main.o pgm_image.o pgm_image.h -o pgm_reader 

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp 

pgm_image.o: pgm_image.cpp pgm_image.h
	${CXX} ${CXXFLAGS} -c pgm_image.cpp

clean:
	rm -f *.o pgm_reader