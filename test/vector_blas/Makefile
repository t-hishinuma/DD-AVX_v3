DD_AVX_DIR?=$(HOME)/lib/dd_avx/

RPATH=-Wl,-rpath,$(DD_AVX_DIR)/lib 
CXXFLAGS=-O3 -std=c++14 -fopenmp -lm
CXXFLAGS=-Wno-class-conversion
LIB=-I$(DD_AVX_DIR)/include -L$(DD_AVX_DIR)/lib -ldd-avx -lqd

OBJS= axpy.o axpyz.o dot.o nrm2.o xpay.o scale.o

all: $(OBJS)

axpy.o : axpy.cpp
	g++ $(RPATH) $(CXXFLAGS) $^ -o $@ $(LIB)

axpyz.o : axpyz.cpp
	g++ $(RPATH) $(CXXFLAGS) $^ -o $@ $(LIB)

xpay.o : xpay.cpp
	g++ $(RPATH) $(CXXFLAGS) $^ -o $@ $(LIB)

scale.o : scale.cpp
	g++ $(RPATH) $(CXXFLAGS) $^ -o $@ $(LIB)

dot.o : dot.cpp
	g++ $(RPATH) $(CXXFLAGS) $^ -o $@ $(LIB)

nrm2.o : nrm2.cpp
	g++ $(RPATH) $(CXXFLAGS) $^ -o $@ $(LIB)

clean:
	- rm $(OBJS)
