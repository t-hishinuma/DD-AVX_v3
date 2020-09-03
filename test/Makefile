all: 
	$(MAKE) -j -C scalar
	$(MAKE) -j -C vector
	$(MAKE) -j -C vector_blas
	$(MAKE) -j -C matrix

clean:
	- $(MAKE) -j -C scalar clean
	- $(MAKE) -j -C vector clean
	- $(MAKE) -j -C vector_blas clean
	- $(MAKE) -j -C matrix clean
