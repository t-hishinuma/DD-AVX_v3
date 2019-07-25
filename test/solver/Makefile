DD_AVX_DIR?=$(HOME)/lib/dd_avx/

RPATH=-Wl,-rpath,$(DD_AVX_DIR)/lib 
LIB=-I$(DD_AVX_DIR)/include -L$(DD_AVX_DIR)/lib -ldd-avx -lqd

OBJS= jacobi.o

all: $(OBJS)

jacobi.o : jacobi.cpp
	g++ $(RPATH) $(LIB) $^ -o $@
