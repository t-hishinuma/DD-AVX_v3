DD_AVX_DIR+=$(HOME)/lib/dd_avx/

all:
	$(MAKE) -C submodules -f Makefile.qd
	$(MAKE) -C submodules -f Makefile.qd install
	$(MAKE) -j -C src/ -f Makefile.avx2 

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
