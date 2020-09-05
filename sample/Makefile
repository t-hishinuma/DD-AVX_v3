DD_AVX_DIR?=$(HOME)/lib/dd_avx

CXX=g++
RPATH=-Wl,-rpath,$(DD_AVX_DIR)/lib 
LIB=-I$(DD_AVX_DIR)/include -L$(DD_AVX_DIR)/lib -ldd-avx -lqd
CXXFLAGS=-O3 -std=c++17 -fopenmp -lm 

OBJS=cg.out

all: $(OBJS)

$(OBJS): cg.cpp
	$(CXX) $(CXXFLAGS) $(RPATH) $^ -o $@ $(LIB)

test: trimat.mtx
	./cg.out ./trimat.mtx

trimat.mtx: trimat_gen.cpp
	g++ trimat_gen.cpp -o trimat_gen.out
	./trimat_gen.out 100 2 > trimat.mtx

clean:
	- rm $(OBJS)
	- rm trimat_gen.out trimat.mtx
