all: 
	make -j -C scalar
	make -j -C vector
	make -j -C vector_blas
	make -j -C matrix

test:
	make -j -C scalar test
	make -j -C vector test
	make -j -C vector_blas test
	make -j -C matrix test

clean:
	- make -j -C scalar clean
	- make -j -C vector clean
	- make -j -C vector_blas clean
	- make -j -C matrix clean
