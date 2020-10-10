![master branch CI status](https://github.com/t-hishinuma/DD-AVX_v3/workflows/C/C++%20CI/badge.svg)

# DD-AVX Library: Library of High Precision Sparse Matrix Operations Accelerated by SIMD

## About
DD-AVX_v3 is SIMD accelerated simple interface high precision BLAS Lv.1 and Sparse BLAS operations Library.

These operations can be performed by combining double and double-double precision.

**Multi-threading** (OpenMP) and **SIMD AVX / AVX2 / AVX512** acceleration are available.

This library provides an easy way to implement a fast and accurate Krylov subspace method.


This library is extensions of 
[Lis_DD_AVXKernals](https://github.com/t-hishinuma/Lis_DD_AVXkernels) and 
[DD-AVX_v2](https://github.com/t-hishinuma/DD-AVX_v2) (archived).

## Interface
This library provides BLAS / Sparse BLAS functions for the following six types.

### Scalar
* d_real (alias of double)
* dd_real (provided by the QD Library)
### Vector
* d_real_vector
* dd_real_vector
### Sparse matrix (CRS format)
* d_real_SpMat

It has BLAS Lv.1 and Sparse BLAS functions for these types.

All combinations of BLAS functions are implemented.
It works for both D and DD types.

See the [axpy sample code](https://github.com/t-hishinuma/DD-AVX_v3/blob/master/test/vector_blas/axpy.cpp) and 
[CG method sample code](https://github.com/t-hishinuma/DD-AVX_v3/blob/master/sample/cg.cpp) 
for more information on how to use it.

# Build and Install
This library requires the QD library for scalar operations as a submodule.
The QD library is downloaded and built automatically by `make`.

You can specify the destination directory with `DD_AVX_DIR` and `make` .
The QD libraries are installed in the same directory.

You can build and install the QD library with the following commands:

## System Requirements
* g++ 7.1 or higher (C++17)
* GNU make

## Build for each SIMD instruction
### AVX
> make avx
> 
> make install

### AVX2
> make avx2
> 
> make install

### AVX512
> make avx512
> 
> make install

#### AVX512 testing is inadequate.
Since github actions's runner does not support AVX512, github actions only verifies the build.
We performed manual testing on an Intel® Xeon® Platinum 8280.


# Document
It can be generated using Doxygen.

# Current Status and Restrictions
This is a beta version, and there are some restrictions and changes planned.

The detailed todo is discussed in [Issue](https://github.com/t-hishinuma/DD-AVX_v3/issues)

* SIMD and OpenMP cannot be disabled. (If you want to change the number of OpenMP threads, do so in the environment variable.)
* The class design will be modified to implement element/row/column operations in the sparse matrix class.
* (SIMD_REG class is difficult to share with Scalar, so I want to change it to REG class.)
* The conversion routine to BCRS format doesn't work because I'm currently trying to rework it to make it multi-threaded.


# Test and sample
## test
We have a complete set of tests for each feature in the `test/` directory. 

> cd test/
> 
> make
> 
> make test_all

## sample
We have implemented an example of the CG method, which is available in `sample/`.
