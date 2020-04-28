#include<DD-AVX.hpp>
using namespace ddavx_core;

void dd_real_vector::minus(){
	registers regs;
	#pragma omp parallel private(regs)
	{
		size_t i=0, is=0, ie=0;
		get_isie(size(), is, ie);

		for(i = is; (int)i < (int)(ie-SIMD_Length+1); i += SIMD_Length){
			to_minus(hi.data()[i], regs);
			to_minus(lo.data()[i], regs);
		}
		for(;i<ie;i++){
			hi[i] = -1 * hi[i];
			lo[i] = -1 * lo[i];
		}
	}
}

void d_real_vector::minus(){
	registers regs;
	#pragma omp parallel private(regs)
	{
		size_t i=0, is=0, ie=0;
		get_isie(size(), is, ie);

		for(i = is; (int)i < (int)(ie-SIMD_Length+1); i += SIMD_Length){
			to_minus(data()[i], regs);
		}
		for(;i<ie;i++){
			data()[i] = -1 * data()[i];
		}
	}
}

dd_real_vector dd_real_vector::operator-()
{
	minus();
	return *this;
}

d_real_vector d_real_vector::operator-()
{
	minus();
	return *this;
}
