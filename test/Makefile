
all: run

build:
	g++ -O3 -I../include -I../lib/qd_include/ -L../lib -ldd-avx -std=c++11 test.cpp -o test.o

run: build
	export LD_LIBRARY_PATH=$(LD_LIBRARY_PATY):~/Work/DD-AVX/DD-AVX/lib/;./test.o
