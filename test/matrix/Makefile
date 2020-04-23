DD_AVX_DIR?=$(HOME)/lib/dd_avx/

RPATH=-Wl,-rpath,$(DD_AVX_DIR)/lib 
LIB=-I$(DD_AVX_DIR)/include -L$(DD_AVX_DIR)/lib -ldd-avx -lqd

OBJS= input.o spmv.o util.o

all: $(OBJS)

input.o : input.cpp
	g++ $(RPATH) $^ -o $@ $(LIB)

spmv.o : spmv.cpp
	g++ $(RPATH) $^ -o $@ $(LIB)

util.o : util.cpp
	g++ $(RPATH) $^ -o $@ $(LIB)

clean:
	- rm $(OBJS)
