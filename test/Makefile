all: 
	make -j -C scalar
	make -j -C vector
	make -j -C vector_blas
	make -j -C matrix

test: test_scalar test_vector test_vector_blas test_matrix

test_scalar:
	make -j -C scalar test

test_vector:
	make -j -C vector test

test_vector_blas:
	make -j -C vector_blas test

test_matrix:
	make -j -C matrix test

test_all:
	make -j -C scalar test
	make -j -C vector test
	make -j -C vector_blas test
	make -j -C matrix test

clean:
	- make -j -C scalar clean
	- make -j -C vector clean
	- make -j -C vector_blas clean
	- make -j -C matrix clean
