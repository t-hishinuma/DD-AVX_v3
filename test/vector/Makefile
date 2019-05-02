DD_AVX_DIR?=$(HOME)/lib/dd_avx/

RPATH=-Wl,-rpath,$(DD_AVX_DIR)/lib 
LIB=-I$(DD_AVX_DIR)/include -L$(DD_AVX_DIR)/lib -ldd-avx -lqd

all: build

build: 
	g++ $(RPATH) $(LIB) vector.cpp -o vector.o

run: build
	./vector.o

clean:
	- rm vector.o
