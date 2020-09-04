DD_AVX_DIR?=$(HOME)/lib/dd_avx

CXX=g++
RPATH=-Wl,-rpath,$(DD_AVX_DIR)/lib 
LIB=-I$(DD_AVX_DIR)/include -L$(DD_AVX_DIR)/lib -lqd -ldd-avx -lqd
CXXFLAGS=-O3 -std=c++14 -fopenmp -lm -DUSE_AVX2

all: $(FUNC).out 

$(FUNC).out: $(FUNC).cpp
	$(CXX) $(CXXFLAGS) $(RPATH) $^ -o $@ $(LIB)
