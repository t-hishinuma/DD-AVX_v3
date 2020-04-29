#include<DD-AVX.hpp>

using namespace ddavx_core;

//=========================================================
//  function
//=========================================================

void d_real_vector::sub(dd_real_vector& vec1, dd_real_vector& vec2)
{
	if(size() != vec1.size() || size() != vec2.size()){
		std::cerr << "error bad vector size" << std::endl;
		assert(1);
	}
	registers regs;

#pragma omp parallel private(regs)
	{
		size_t i=0, is=0, ie=0;
		get_isie(size(), is, ie);
		for(i = is; (int)i < (int)(ie-SIMD_Length+1); i += SIMD_Length){
			SIMDreg a_hi = load(data()[i]);

			SIMDreg b_hi = load(vec1.hi[i]);
			SIMDreg b_lo = load(vec1.lo[i]);

			SIMDreg c_hi = load(vec2.hi[i]);
			SIMDreg c_lo = load(vec2.lo[i]);
			to_minus(c_hi, regs);
			to_minus(c_lo, regs);

			Add(a_hi, b_hi, b_lo, c_hi, c_lo, regs);

			store(data()[i], a_hi);
		}
		for(;i<ie;i++){
			Add(data()[i], vec1.hi[i], vec1.lo[i], -vec2.hi[i], -vec2.lo[i]);
		}
	}
}

void d_real_vector::sub(d_real_vector& vec1, dd_real_vector& vec2)
{
	if(size() != vec1.size() || size() != vec2.size()){
		std::cerr << "error bad vector size" << std::endl;
		assert(1);
	}
	registers regs;
	double *vv = data();

#pragma omp parallel private(regs)
	{
		size_t i=0, is=0, ie=0;
		get_isie(size(), is, ie);
		for(i = is; (int)i < (int)(ie-SIMD_Length+1); i += SIMD_Length){
			SIMDreg a_hi = load(data()[i]);

			SIMDreg b_hi = load(vec1.data()[i]);
			SIMDreg b_lo = regs.zeros;

			SIMDreg c_hi = load(vec2.hi[i]);
			SIMDreg c_lo = load(vec2.lo[i]);
			to_minus(c_hi, regs);
			to_minus(c_lo, regs);

			Add(a_hi, b_hi, b_lo, c_hi, c_lo, regs);

			store(data()[i], a_hi);
		}
		for(;i<ie;i++){
			Add(data()[i], vec1.data()[i], 0.0, -1 * vec2.hi[i], -1 * vec2.lo[i]);
		}
	}
}

void d_real_vector::sub(dd_real_vector& vec1, d_real_vector& vec2)
{
	if(size() != vec1.size() || size() != vec2.size()){
		std::cerr << "error bad vector size" << std::endl;
		assert(1);
	}
	registers regs;
	double *vv = data();

#pragma omp parallel private(regs)
	{
		size_t i=0, is=0, ie=0;
		get_isie(size(), is, ie);
		for(i = is; (int)i < (int)(ie-SIMD_Length+1); i += SIMD_Length){
			SIMDreg a_hi = load(data()[i]);

			SIMDreg b_hi = load(vec1.hi[i]);
			SIMDreg b_lo = load(vec1.lo[i]);

			SIMDreg c_hi = load(vec2.data()[i]);
			SIMDreg c_lo = regs.zeros;

			to_minus(c_hi, regs);
			to_minus(c_lo, regs);

			Add(a_hi, b_hi, b_lo, c_hi, c_lo, regs);

			store(data()[i], a_hi);
		}
		for(;i<ie;i++){
			Add(data()[i], vec1.hi[i], vec1.lo[i], -1 * vec2.data()[i], -1 * 0.0);
		}
	}
}

void d_real_vector::sub(d_real_vector& vec1, d_real_vector& vec2)
{
	if(size() != vec1.size() || size() != vec2.size()){
		std::cout << "error vecvor size is" << size() << vec1.size() << vec2.size() << std::endl;
		assert(1);
	}

#pragma omp parallel for
	for(size_t i = 0; i < size(); i++){
		data()[i] = vec1.data()[i] - vec2.data()[i];
	}
}

//=========================================================
//  operator
//=========================================================
d_real_vector d_real_vector::operator-(dd_real_vector& vec)
{
	sub(*this, vec);
	return *this;
}
d_real_vector d_real_vector::operator-=(dd_real_vector& vec)
{
	sub(*this, vec);
	return *this;
}

d_real_vector d_real_vector::operator-(d_real_vector& vec)
{
	sub(*this, vec);
	return *this;
}
d_real_vector d_real_vector::operator-=(d_real_vector& vec)
{
	sub(*this, vec);
	return *this;
}

