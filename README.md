![master branch CI status](https://github.com/t-hishinuma/DD-AVX_v3/workflows/C/C++%20CI/badge.svg)

# DD-AVX Library: Library of High Precision Sparse Matrix Operations Accelerated by intel SIMD instructions

## About
DD-AVX_v3 is SIMD accelerated simple interface high precision BLAS / Sparse BLAS Library.

This library provides an easy way to implement a fast and accurate Krylov subspace method.

OpenMP and SIMD AVX / AVX2 speedup are available.

This library is extensions of 
[Lis_DD_AVXKernals](https://github.com/t-hishinuma/Lis_DD_AVXkernels) and 
[DD-AVX_v2](https://github.com/t-hishinuma/DD-AVX_v2) (archived).

## Interface
This library provides BLAS / Sparse BLAS functions for the following six types.

### Scalar
* double
* dd_real (provided by the QD Library)
### Vector
* d_real_vector
* dd_real_vector
### Sparse matrix
* d_real_SpMat
* dd_real_SpMat

It has BLAS Lv 1 and Sparse BLAS functions for these types.

All combinations of BLAS functions are implemented.
It works for both D and DD types.

See the [axpy sample code](https://github.com/t-hishinuma/DD-AVX_v3/blob/master/test/vector_blas/axpy.cpp) for more information on how to use it.

# Build and Install
This library requires the QD library for scalar operations as a submodule.
The QD library is downloaded and built automatically by `make`.

You can specify the destination directory with `DDAVX_DIR' and `make` .
The QD libraries are installed in the same directory.

You can build and install the QD library with the following commands:

## AVX
> make avx
> 
> make install

## AVX2
> make avx2
> 
> make install

## AVX512 (not yet implemented)
In the future, AVX512 can be built with the following command.
> make avx512
> 
> make install

# System Requirements
* g++ 7.1 or higher
* GNU make

# Current Status and Restrictions
This is a beta version, and there are some restrictions and changes planned.

* SIMD and OpenMP cannot be disabled. (If you want to change the number of OpenMP threads, do so in the environment variable.)
* The class design will be modified to implement element/row/column operations in the sparse matrix class.
* (SIMD_REG class is difficult to share with Scalar, so I want to change it to REG class.)
* The conversion routine to BCRS format doesn't work because I'm currently trying to rework it to make it multi-threaded.

# Document
It can be generated using Doxygen.

# Testing
We have a complete set of tests for each feature in the test directory. You can find them in the test directory.

> cd test/
> 
> make
> 
> make test
