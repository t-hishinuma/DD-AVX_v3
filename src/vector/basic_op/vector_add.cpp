#include<DD-AVX.hpp>

using namespace ddavx_core;

void dd_real_vector::add(const dd_real_vector& vec1, const dd_real_vector& vec2)
{
	if(size() != vec1.size() || size()!= vec2.size()){
		std::cout << "error vecvor size is" << size() << vec1.size() << vec2.size() << std::endl;
		assert(1);
	};
	registers regs;

#pragma omp parallel private(regs)
{
	printf("hello2\n");

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



// #if USE_AVX==1
//    nprocs = omp_get_max_threads();
// #pragma omp parallel private(i,bh,ch,sh,wh,th,bl,cl,sl,wl,tl,p1,p2,t0,t1,t2,eh,t3,is,ie,my_rank)
// {
//		 nprocs = omp_get_max_threads();
//       my_rank = omp_get_thread_num();
//
//       DD_AVX_GET_ISIE(my_rank,nprocs,n,is,ie);
//       for(i=is;i<ie-(DD_AVX_AVX_SIZE-1);i+=DD_AVX_AVX_SIZE)
//       {
// 	 DD_AVX_FMAN_AVX(y[i],yl[i],y[i],yl[i],alpha_hi,alpha_lo,x[i],xl[i]);
//       }
//       for(;i<ie;i++)
//       {
// 	 DD_AVX_FMA_SSE2(y[i],yl[i],y[i],yl[i],alpha.hi,alpha.lo,x[i],xl[i]);
//       }


}
