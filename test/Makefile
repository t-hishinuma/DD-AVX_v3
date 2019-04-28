DD_AVX_DIR?=$(HOME)/lib/dd_avx/

RPATH=-Wl,-rpath,$(DD_AVX_DIR)/lib 
LIB=-I$(DD_AVX_DIR)/include -L$(DD_AVX_DIR)/lib -ldd-avx 

all: run

build:
	g++ $(RPATH) $(LIB) test.cpp -o test.o
run: build
	./test.o

