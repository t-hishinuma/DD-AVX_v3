DD_AVX_DIR?=$(HOME)/lib/dd_avx/

RPATH=-Wl,-rpath,$(DD_AVX_DIR)/lib  -w
LIB=-I$(DD_AVX_DIR)/include -L$(DD_AVX_DIR)/lib -ldd-avx  -lqd

all: build

build: 
	g++ $(RPATH) $(LIB) scalar.cpp -o scalar.o
	g++ $(RPATH) $(LIB) vector_element.cpp -o vector_element.o

run: build
	./scalar.o

clean:
	rm scalar.o

