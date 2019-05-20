DD_AVX_DIR?=$(HOME)/lib/dd_avx/

RPATH=-Wl,-rpath,$(DD_AVX_DIR)/lib 
CXXFLAGS=-O3 -fopenmp -lm
LIB=-I$(DD_AVX_DIR)/include -L$(DD_AVX_DIR)/lib -ldd-avx -lqd

OBJS= axpy.o 

all: $(OBJS)

axpy.o : axpy.cpp
	g++ $(RPATH) $(LIB) $(CXXFLAGS) $^ -o $@

clean:
	- rm $(OBJS)
