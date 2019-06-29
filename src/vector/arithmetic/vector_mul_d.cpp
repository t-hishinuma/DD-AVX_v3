#include<DD-AVX.hpp>

using namespace ddavx_core;

//=========================================================
//  function
//=========================================================

void d_real_vector::mul(dd_real_vector& vec1, dd_real_vector& vec2)
{
	if((long)size() != (long)vec1.size() || (long)size() != (long)vec2.size()){
		std::cerr << "error bad vector size" << std::endl;
		assert(1);
	}
	registers regs;

#pragma omp parallel private(regs)
	{
		long i=0, is=0, ie=0;
		get_isie(size(), is, ie);
		for(i = is; i < ie - AVX_SIZE - 1; i += AVX_SIZE){
			AVXreg a_hi = load(data()[i]);

			AVXreg b_hi = load(vec1.hi[i]);
			AVXreg b_lo = load(vec1.lo[i]);

			AVXreg c_hi = load(vec2.hi[i]);
			AVXreg c_lo = load(vec2.lo[i]);

			Mul(a_hi, b_hi, b_lo, c_hi, c_lo, regs);

			store(data()[i], a_hi);
		}
		for(;i<ie;i++){
			Mul(data()[i], vec1.hi[i], vec1.lo[i], vec2.hi[i], vec2.lo[i]);
		}
	}
}

void d_real_vector::mul(dd_real_vector& vec1, d_real_vector& vec2)
{
	if((long)size() != (long)vec1.size() || (long)size() != (long)vec2.size()){
		std::cerr << "error bad vector size" << std::endl;
		assert(1);
	}
	registers regs;
	double *vv = data();

#pragma omp parallel private(regs)
	{
		long i=0, is=0, ie=0;
		get_isie(size(), is, ie);
		for(i = is; i < ie - AVX_SIZE - 1; i += AVX_SIZE){
			AVXreg a_hi = load(data()[i]);

			AVXreg b_hi = load(vec1.hi[i]);
			AVXreg b_lo = load(vec1.lo[i]);

			AVXreg c_hi = load(vec2.data()[i]);
			AVXreg c_lo = regs.zeros;

			Mul(a_hi, b_hi, b_lo, c_hi, c_lo, regs);

			store(data()[i], a_hi);
		}
		for(;i<ie;i++){
			Mul(data()[i], vec1.hi[i], vec1.lo[i], vec2.data()[i], 0.0);
		}
	}
}

void d_real_vector::mul(d_real_vector& vec1, dd_real_vector& vec2)
{
 	mul(vec2, vec1);
}

void d_real_vector::mul(d_real_vector& vec1, d_real_vector& vec2)
{
	if((long)size() != (long)vec1.size() || (long)size() != (long)vec2.size()){
		std::cerr << "error bad vector size" << std::endl;
		assert(1);
	}

#pragma omp parallel for
	for(long i = 0; i < (long)size(); i++){
		data()[i] = vec1.data()[i] * vec2.data()[i];

	}
}

//=========================================================
//  operator
//=========================================================
d_real_vector d_real_vector::operator*(dd_real_vector& vec)
{
	mul(*this, vec);
	return *this;
}
d_real_vector d_real_vector::operator*=(dd_real_vector& vec)
{
	mul(*this, vec);
	return *this;
}

d_real_vector d_real_vector::operator*(d_real_vector& vec)
{
	mul(*this, vec);
	return *this;
}
d_real_vector d_real_vector::operator*=(d_real_vector& vec)
{
	mul(*this, vec);
	return *this;
}

