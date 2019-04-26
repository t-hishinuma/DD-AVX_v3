
DD-AVX_DIR=src/obj
TARGET = $(DD-AVX_DIR)/a.out

QD_DIR=lib/qd
QD=lib/qd/lib/libqd.a

all: $(TARGET) $(QD)
$(TARGET): src/a.cpp $(QD)
	mkdir -p src/obj
	g++ src/a.cpp -o src/obj/a.out

$(QD):
	$(MAKE) -C submodules -f Makefile.qd
	$(MAKE) -C submodules -f Makefile.qd install

