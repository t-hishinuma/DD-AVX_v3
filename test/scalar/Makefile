DD_AVX_DIR?=$(HOME)/lib/dd_avx/

RPATH=-Wl,-rpath,$(DD_AVX_DIR)/lib 
LIB=-I$(DD_AVX_DIR)/include -L$(DD_AVX_DIR)/lib -ldd-avx  -lqd

all: build

build: scalar.o
	g++ $(RPATH) $(LIB) scalar.cpp -o scalar.o

run: build
	./scalar.o

clean:
	rm scalar.o

