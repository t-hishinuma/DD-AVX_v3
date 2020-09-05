! [C/C++ CI](https://github.com/t-hishinuma/DD-AVX_v3/workflows/C/C++%20CI/badge.svg?branch=master)

# DD-AVX Library (beta): Library of High Precision Sparse Matrix Operations Accelerated by SIMD AVX2
# About
DD-AVX is a library with a simple interface and is intended to be used in combination with double / double-double precision.

This library is extensions of Lis_DD_AVXKernals and DD-AVX_v2 (archived)
This library provides an easy way to implement a fast and accurate Krylov subspace method.
OpenMP and SIMD AVX / AVX2 speedup are available.

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

See the axpy sample code for more information on how to use it.

# Build and Install
This library requires the QD library for scalar operations as a submodule.
The QD library is downloaded and built automatically by `make`.

You can specify the destination directory with `DDAVX_DIR' and `make'.
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

# For Developer
In the include, each of the following is a

Declaration of DD-AVX.hpp BLAS / Sparse BLAS functions
DD-AVX_d_spmat.hpp Definition of double-precision sparse matrix type
DD-AVX_d_vector.hpp double-precision vector type definition (inherits from std::vector)
DD-AVX_dd_vector.hpp Definition of the double-precision vector type
Core/AVX2 AVX2 implementation of Add, Mul and Integration operations on AVX2ized DD
Both template type and overloaded type of internal operations are implemented. We have confirmed that they have the same performance. Switching is done by ifdef in include/DD-AVX.hpp

Translated with www.DeepL.com/Translator (free version)
