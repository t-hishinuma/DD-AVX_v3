DD_AVX_DIR?=$(HOME)/lib/dd_avx/

RPATH=-Wl,-rpath,$(DD_AVX_DIR)/lib 
LIB=-I$(DD_AVX_DIR)/include -L$(DD_AVX_DIR)/lib -ldd-avx -lqd

all: build

build: 
	g++ $(RPATH) $(LIB) vector_std.cpp -o vector_std.o
	g++ $(RPATH) $(LIB) vector_copy.cpp -o vector_copy.o
	g++ $(RPATH) $(LIB) vector_copy.cpp -o vector_add.o

run: build
	./vector_std.o
	./vector_copy.o
	./vector_add.o

clean:
	- rm vector_std.o vector_copy.o vector_add.o
