DD_AVX_DIR?=$(HOME)/lib/dd_avx/

RPATH=-Wl,-rpath,$(DD_AVX_DIR)/lib 
LIB=-I$(DD_AVX_DIR)/include -L$(DD_AVX_DIR)/lib -ldd-avx -lqd

OBJS= std.o copy.o minus.o add.o sub.o

all: $(OBJS)

std.o : std.cpp
	g++ $(RPATH) $(LIB) $^ -o $@

copy.o : copy.cpp
	g++ $(RPATH) $(LIB) $^ -o $@

minus.o : minus.cpp
	g++ $(RPATH) $(LIB) $^ -o $@

add.o : add.cpp
	g++ $(RPATH) $(LIB) $^ -o $@

sub.o : sub.cpp
	g++ $(RPATH) $(LIB) $^ -o $@

clean:
	- rm $(OBJS)
