DD_AVX_DIR?=$(HOME)/lib/dd_avx/

RPATH=-Wl,-rpath,$(DD_AVX_DIR)/lib 
LIB=-I$(DD_AVX_DIR)/include -L$(DD_AVX_DIR)/lib -ldd-avx -lqd
CXXFLAGS=-O3 -std=c++14 -DUSE_AVX2

OBJS= input.o spmv.o util.o

all: $(OBJS)

input.o : input.cpp
	g++ $(CXXFLAGS) $(RPATH) $^ -o $@ $(LIB)

spmv.o : spmv.cpp
	g++ $(CXXFLAGS) $(RPATH) $^ -o $@ $(LIB)

util.o : util.cpp
	g++ $(CXXFLAGS) $(RPATH) $^ -o $@ $(LIB)

clean:
	- rm $(OBJS)
