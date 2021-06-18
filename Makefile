ALLGEBRA_IMAGE := ghcr.io/ricosjp/allgebra
ALLGEBRA_TAG   := 21.05.0
DD_AVX_DIR?=$(HOME)/lib/dd_avx/

all: avx2

avx512:
	git submodule update -i
	$(MAKE) -C submodules -f Makefile.qd
	$(MAKE) -C submodules -f Makefile.qd install
	mkdir -p src/obj
	$(MAKE) -j -C src/ -f Makefile.avx512

avx2:
	git submodule update -i
	$(MAKE) -C submodules -f Makefile.qd
	$(MAKE) -C submodules -f Makefile.qd install
	mkdir -p src/obj
	$(MAKE) -j -C src/ -f Makefile.avx2 

avx:
	git submodule update -i
	$(MAKE) -C submodules -f Makefile.qd
	$(MAKE) -C submodules -f Makefile.qd install
	mkdir -p src/obj
	$(MAKE) -j -C src/ -f Makefile.avx

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
	- rm -rf  $(DD_AVX_DIR)/lib/
	- rm -rf  $(DD_AVX_DIR)/include/
	- $(MAKE) -C submodules -f Makefile.qd clean

clean_lib:
	- rm -rf src/obj/*
	- rm -rf ./lib/libdd-avx.so
	- rm -rf  $(DD_AVX_DIR)/lib/
	- rm -rf  $(DD_AVX_DIR)/include/

format:
	docker run -it --rm  \
		-u `id -u`:`id -g` \
		-v $(PWD):$(PWD)   \
		-w $(PWD)          \
		$(ALLGEBRA_IMAGE)/clang-format:$(ALLGEBRA_TAG) /usr/bin/check_format.sh
