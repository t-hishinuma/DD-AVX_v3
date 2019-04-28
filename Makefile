DD-AVX_DIR=./lib/
TARGET=$(DD-AVX_DIR)/libdd-avx.so

QD_LIB=lib/qd_lib/libqd.a

CXXFLAGS+=-O3 -std=c++11 -g -Wall -Wno-unused-variable -fPIC
LIBFLAGS=-shared 

SRCS=src/a.cpp 
SRCS2=src/b.cpp 
 
$(TARGET): $(QD_LIB) src/obj/a.o 
	g++ $(LIBFLAGS) src/obj/a.o lib/qd/libqd.a src/obj/b.o -o $(TARGET)

src/obj/a.o: src/a.cpp src/b.cpp
	mkdir -p src/obj
	g++ $(CXXFLAGS) -c $(SRCS) -I./include -o src/obj/a.o
	g++ $(CXXFLAGS) -c $(SRCS2) -I./include -o src/obj/b.o

$(QD_LIB):
	git submodule update -i
	$(MAKE) -C submodules -f Makefile.qd
	$(MAKE) -C submodules -f Makefile.qd install

clean:
	- rm -r src/obj
	- rm $(TARGET)
