DD_AVX_DIR?=$(HOME)/lib/dd_avx/

RPATH=-Wl,-rpath,$(DD_AVX_DIR)/lib  -w
LIB=-I$(DD_AVX_DIR)/include -L$(DD_AVX_DIR)/lib -ldd-avx -lqd
CXXFLAGS=-O3 -std=c++14 -fopenmp -lm -DUSE_AVX2

all: build

build: 
	g++ $(RPATH) $(CXXFLAGS) scalar.cpp -o scalar.o $(LIB)
	g++ $(RPATH) $(CXXFLAGS) vector_element.cpp -o vector_element.o $(LIB) 

run: build
	./scalar.o
	./vector_element.o

clean:
	rm scalar.o

