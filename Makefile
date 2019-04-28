DD_AVX_DIR+=$(HOME)/lib/dd_avx/

TARGET=lib/libdd-avx.so

QD_LIB=./lib/libqd.a

CXXFLAGS+=-O3 -std=c++11 -lm -g -Wall -Wno-unused-variable -fPIC 
LIBFLAGS=-shared
QD_LINK=-I./include/ -L./lib/ -lqd

SRCS=src/a.cpp 
SRCS2=src/b.cpp 
 
$(TARGET): $(QD_LIB) src/obj/a.o 
	g++ $(LIBFLAGS) $(QD_LINK) src/obj/a.o src/obj/b.o -o $(TARGET)

src/obj/a.o: src/a.cpp src/b.cpp $(QD_LIB)
	mkdir -p src/obj
	g++ $(CXXFLAGS) $(QD_LINK) -c $(SRCS) -I./include -o src/obj/a.o
	g++ $(CXXFLAGS) $(QD_LINK) -c $(SRCS2) -I./include -o src/obj/b.o

$(QD_LIB):
	git submodule update -i
	$(MAKE) -C submodules -f Makefile.qd
	$(MAKE) -C submodules -f Makefile.qd install

install:
	mkdir -p $(DD_AVX_DIR)
	cp -r ./lib $(DD_AVX_DIR)
	cp -r ./include $(DD_AVX_DIR)

clean:
	- rm -rf src/obj
	- rm -rf ./lib/*
	- rm -rf  $(DD_AVX_DIR)
	- rm -rf include/qd
	- $(MAKE) -C submodules -f Makefile.qd clean
