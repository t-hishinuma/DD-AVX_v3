#include<DD-AVX.hpp>

using namespace ddavx_core;

//=========================================================
//  function
//=========================================================

//DD=DD+DD
void dd_real_vector::add(const dd_real_vector& vec1, const dd_real_vector& vec2)
{
	if(size() != vec1.size() || size() != vec2.size()){
		std::cout << "error vecvor size is" << size() << vec1.size() << vec2.size() << std::endl;
		assert(1);
	};
	registers regs;

#pragma omp parallel private(regs)
	{
		long i=0, is=0, ie=0;
		get_isie(size(), is, ie);
		for(i = is; i < ie - AVX_SIZE - 1; i += AVX_SIZE){
			AVXreg a_hi = load(hi[i]);
			AVXreg a_lo = load(lo[i]);

			AVXreg b_hi = load(vec1.hi[i]);
			AVXreg b_lo = load(vec1.lo[i]);

			AVXreg c_hi = load(vec2.hi[i]);
			AVXreg c_lo = load(vec2.lo[i]);

			Add(a_hi, a_lo, b_hi, b_lo, c_hi, c_lo, regs);

			store(hi[i], a_hi);
			store(lo[i], a_lo);
		}
		for(;i<ie;i++){
			Add(hi[i], lo[i], vec1.hi[i], vec1.lo[i], vec2.hi[i], vec2.lo[i]);
		}
	}
}

//DD=D+DD
void dd_real_vector::add(const d_real_vector& vec1, const dd_real_vector& vec2)
{
	if(size() != (long)vec1.size() || size() != vec2.size()){
		std::cout << "error vecvor size is" << size() << vec1.size() << vec2.size() << std::endl;
		assert(1);
	};
	registers regs;

#pragma omp parallel private(regs)
	{
		long i=0, is=0, ie=0;
		get_isie(size(), is, ie);
		for(i = is; i < ie - AVX_SIZE - 1; i += AVX_SIZE){
			AVXreg a_hi = load(hi[i]);
			AVXreg a_lo = load(lo[i]);

			AVXreg b_hi = load(vec1[i]);
			AVXreg b_lo = regs.zeros;

			AVXreg c_hi = load(vec2.hi[i]);
			AVXreg c_lo = load(vec2.lo[i]);

			Add(a_hi, a_lo, b_hi, b_lo, c_hi, c_lo, regs);

			store(hi[i], a_hi);
			store(lo[i], a_lo);
		}
		for(;i<ie;i++){
			Add(hi[i], lo[i], vec1[i], 0.0, vec2.hi[i], vec2.lo[i]);
		}
	}
}


//DD=D+DD
void dd_real_vector::add(const dd_real_vector& vec1, const d_real_vector& vec2)
{
	add(vec2, vec1);
}

//DD=D+D
void dd_real_vector::add(const d_real_vector& vec1, const d_real_vector& vec2)
{
	if(size() != (long)vec1.size() || size() != (long)vec2.size()){
		std::cout << "error vecvor size is" << size() << vec1.size() << vec2.size() << std::endl;
		assert(1);
	};

#pragma omp parallel for
	for(long i = 0; i < size(); i++){
		hi[i] = vec1[i] + vec2[i];
		lo[i] = 0.0;
			
	}
}

//=========================================================
//  operator
//=========================================================
//DD=DD+DD
dd_real_vector dd_real_vector::operator+(const dd_real_vector& vec)
{
	add(*this, vec);
	return *this;
}
dd_real_vector dd_real_vector::operator+=(const dd_real_vector& vec)
{
	add(*this, vec);
	return *this;
}

//DD=DD+D
dd_real_vector dd_real_vector::operator+(const d_real_vector& vec)
{
	add(*this, vec);
	return *this;
}
dd_real_vector dd_real_vector::operator+=(const d_real_vector& vec)
{
	add(*this, vec);
	return *this;
}
