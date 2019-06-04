DD_AVX_DIR?=$(HOME)/lib/dd_avx/
DD_AVX_INC?=$(HOME)/lib/dd_avx/

all:
	git submodule update -i
	$(MAKE) -C submodules -f Makefile.qd
	$(MAKE) -C submodules -f Makefile.qd install
	$(MAKE) -j -C src/ -f Makefile.avx2 

install:
	mkdir -p $(DD_AVX_DIR)
	mkdir -p $(DD_AVX_INC)
	cp -r ./lib/* $(DD_AVX_DIR)
	cp -r ./include/* $(DD_AVX_INC)

clean:
	- rm -rf src/obj
	- rm -rf ./lib/*
	- rm -rf  $(DD_AVX_DIR)
	- rm -rf include/qd
	- rm -rf ./lib/libdd-avx.so
	- rm -rf  $(DD_AVX_DIR)/libqd.*
	- rm -rf  $(DD_AVX_DIR)/libdd-avx.*
	- rm -rf  $(DD_AVX_INC)/DD-AVX*
	- rm -rf  $(DD_AVX_INC)/qd
	- $(MAKE) -C submodules -f Makefile.qd clean

clean_lib:
	- rm -rf src/obj/*
	- rm -rf ./lib/libdd-avx.so
	- rm -rf  $(DD_AVX_DIR)/lib/libqd.*
	- rm -rf  $(DD_AVX_DIR)/lib/libdd-avx.*
	- rm -rf  $(DD_AVX_INC)/include/DD-AVX*
	- rm -rf  $(DD_AVX_INC)/include/qd
