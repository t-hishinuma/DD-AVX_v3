#include<DD-AVX_internal.hpp>

using namespace ddavx_core;

//=========================================================
//  function
//=========================================================

void d_real_vector::div(dd_real_vector& vec1, dd_real_vector& vec2)
{
	if(size() != vec1.size() || size() != vec2.size()){
		std::cerr << "error bad vector size" << std::endl;
		assert(1);
	}

#pragma omp parallel for
	for(size_t i=0 ; i<size() ; i++){
		dd_real a, b, c;
		a.x[0] = data()[i];
		a.x[1] = 0.0;
		b.x[0] = vec1.hi[i];
		b.x[1] = vec1.lo[i];
		c.x[0] = vec2.hi[i];
		c.x[1] = vec2.lo[i];
		a = b / c;
		data()[i] = a.x[0];
	}
}

void d_real_vector::div(d_real_vector& vec1, dd_real_vector& vec2)
{
	if(size() != vec1.size() || size() != vec2.size()){
		std::cerr << "error bad vector size" << std::endl;
		assert(1);
	}

#pragma omp parallel for
	for(size_t i=0 ; i<size() ; i++){
		dd_real a, b, c;
		a.x[0] = data()[i];
		a.x[1] = 0.0;
		b.x[0] = vec1.data()[i];
		b.x[1] = 0.0;
		c.x[0] = vec2.hi[i];
		c.x[1] = vec2.lo[i];
		a = b / c;
		data()[i] = a.x[0];
	}
}

void d_real_vector::div(dd_real_vector& vec1, d_real_vector& vec2)
{
	if(size() != vec1.size() || size() != vec2.size()){
		std::cerr << "error bad vector size" << std::endl;
		assert(1);
	}

#pragma omp parallel for
	for(size_t i=0 ; i<size() ; i++){
		dd_real a, b, c;
		a.x[0] = data()[i];
		a.x[1] = 0.0;
		b.x[0] = vec1.hi[i];
		b.x[1] = vec1.lo[i];
		c.x[0] = vec2.data()[i];
		c.x[1] = 0.0;
		a = b / c;
		data()[i] = a.x[0];
	}
}

void d_real_vector::div(d_real_vector& vec1, d_real_vector& vec2)
{
	if(size() != vec1.size() || size() != vec2.size()){
		std::cerr << "error bad vector size" << std::endl;
		assert(1);
	}

#pragma omp parallel for
	for(size_t i=0 ; i<size() ; i++){
		data()[i] = vec1.data()[i] / vec2.data()[i];
	}
}

//=========================================================
//  operator
//=========================================================
d_real_vector d_real_vector::operator/(dd_real_vector& vec)
{
	div(*this, vec);
	return *this;
}
d_real_vector d_real_vector::operator/=(dd_real_vector& vec)
{
	div(*this, vec);
	return *this;
}

d_real_vector d_real_vector::operator/(d_real_vector& vec)
{
	div(*this, vec);
	return *this;
}
d_real_vector d_real_vector::operator/=(d_real_vector& vec)
{
	div(*this, vec);
	return *this;
}

