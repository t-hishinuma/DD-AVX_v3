#include<DD-AVX.hpp>

using namespace ddavx_core;

void dd_real_vector::add(const dd_real_vector& vec1, const dd_real_vector& vec2)
{
	registers regs;
	AVXreg a_hi = load(this->hi[0]);
	AVXreg a_lo = load(this->lo[0]);

	store(this->hi[0], a_hi);
	store(this->lo[0], a_lo);


// #if USE_AVX==1
//    nprocs = omp_get_max_threads();
// #pragma omp parallel private(i,bh,ch,sh,wh,th,bl,cl,sl,wl,tl,p1,p2,t0,t1,t2,eh,t3,is,ie,my_rank)
// {
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
