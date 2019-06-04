DD_AVX_DIR?=$(HOME)/lib/dd_avx/

RPATH=-Wl,-rpath,$(DD_AVX_DIR)/lib 
CXXFLAGS=-O3 -fopenmp -lm
LIB=-I$(DD_AVX_DIR)/include -L$(DD_AVX_DIR)/lib -ldd-avx -lqd

OBJS= axpy.o axpyz.o dot.o nrm2.o xpay.o scale.o

all: $(OBJS)

axpy.o : axpy.cpp
	g++ $(RPATH) $(LIB) $(CXXFLAGS) $^ -o $@

axpyz.o : axpyz.cpp
	g++ $(RPATH) $(LIB) $(CXXFLAGS) $^ -o $@

xpay.o : xpay.cpp
	g++ $(RPATH) $(LIB) $(CXXFLAGS) $^ -o $@

scale.o : scale.cpp
	g++ $(RPATH) $(LIB) $(CXXFLAGS) $^ -o $@

dot.o : dot.cpp
	g++ $(RPATH) $(LIB) $(CXXFLAGS) $^ -o $@

nrm2.o : nrm2.cpp
	g++ $(RPATH) $(LIB) $(CXXFLAGS) $^ -o $@

clean:
	- rm $(OBJS)
