DD_AVX_DIR?=$(HOME)/lib/dd_avx/

PHONY: avx2
PHONY: avx512

all: avx2

avx2:
	git submodule update -i
	$(MAKE) -C submodules -f Makefile.qd
	$(MAKE) -C submodules -f Makefile.qd install
	$(MAKE) -j -C src/ -f Makefile.avx2 

avx512:
	git submodule update -i
	$(MAKE) -C submodules -f Makefile.qd
	$(MAKE) -C submodules -f Makefile.qd install
	$(MAKE) -j -C src/ -f Makefile.avx512

install:
	mkdir -p $(DD_AVX_DIR)/lib/
	mkdir -p $(DD_AVX_DIR)/include/
	cp -r ./lib/* $(DD_AVX_DIR)/lib/
	cp -r ./include/* $(DD_AVX_DIR)/include/

clean:
	- rm -rf src/obj
	- rm -rf ./lib/*
	- rm -rf include/qd
	- rm -rf ./lib/libdd-avx.so
	- rm -rf  $(DD_AVX_DIR)/lib/libqd.*
	- rm -rf  $(DD_AVX_DIR)/lib/libdd-avx.*
	- rm -rf  $(DD_AVX_DIR)/include/DD-AVX*
	- rm -rf  $(DD_AVX_DIR)/include/qd
	- $(MAKE) -C submodules -f Makefile.qd clean

clean_lib:
	- rm -rf src/obj/*
	- rm -rf ./lib/libdd-avx.so
	- rm -rf  $(DD_AVX_DIR)/lib/libqd.*
	- rm -rf  $(DD_AVX_DIR)/lib/libdd-avx.*
	- rm -rf  $(DD_AVX_DIR)/include/DD-AVX*
	- rm -rf  $(DD_AVX_DIR)/include/qd
