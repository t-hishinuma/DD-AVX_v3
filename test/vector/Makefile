DD_AVX_DIR?=$(HOME)/lib/dd_avx

RPATH=-Wl,-rpath,$(DD_AVX_DIR)/lib 
LIB=-I$(DD_AVX_DIR)/include -L$(DD_AVX_DIR)/lib -lqd -ldd-avx -lqd
CXXFLAGS=-O3 -std=c++14 -fopenmp -lm -DUSE_AVX2

OBJS= std.o copy.o minus.o add.o sub.o mul.o div.o

all: $(OBJS)

std.o : std.cpp
	g++ $(CXXFLAGS) $(RPATH) $^ -o $@ $(LIB)

copy.o : copy.cpp
	g++ $(CXXFLAGS) $(RPATH) $^ -o $@ $(LIB)

minus.o : minus.cpp
	g++ $(CXXFLAGS) $(RPATH) $^ -o $@ $(LIB)

add.o : add.cpp
	g++ $(CXXFLAGS) $(RPATH) $^ -o $@ $(LIB)

sub.o : sub.cpp
	g++ $(CXXFLAGS) $(RPATH) $^ -o $@ $(LIB)

mul.o : mul.cpp
	g++ $(CXXFLAGS) $(RPATH) $^ -o $@ $(LIB)

div.o : div.cpp
	g++ $(CXXFLAGS) $(RPATH) $^ -o $@ $(LIB)

clean:
	- rm $(OBJS)
