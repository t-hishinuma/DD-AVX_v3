DD_AVX_DIR?=$(HOME)/lib/dd_avx/

RPATH=-Wl,-rpath,$(DD_AVX_DIR)/lib 
LIB=-I$(DD_AVX_DIR)/include -L$(DD_AVX_DIR)/lib -ldd-avx -lqd

OBJS= input.o spmv.o

all: $(OBJS)

input.o : input.cpp
	g++ $(RPATH) $(LIB) $^ -o $@

spmv.o : spmv.cpp
	g++ $(RPATH) $(LIB) $^ -o $@

clean:
	- rm $(OBJS)
