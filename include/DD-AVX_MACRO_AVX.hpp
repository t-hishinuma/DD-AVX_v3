/* Copyright (C) T.Hishinuma, All rights reserved.*/
#ifndef DD_AVX_MACRO_AVX_H_
#define DD_AVX_MACRO_AVX_H_

#ifndef USE_SSE2
	#define USE_SSE2 1
	#define USE_FMA2_SSE2
#endif
#define DD_AVX_AVX_SIZE 4

#include <immintrin.h>
#include <emmintrin.h>

#define SPLITTER 134217729.0

#define DD_AVX_VEC_CAST(VAR) (*(__m128d*)&(VAR))
#define DD_AVX_AVX_TYPE __m256d
#define DD_AVX_AVX_FUNC(NAME) _mm256_##NAME
#define DD_AVX_DECLAR \
   	double DD_AVX_SP = SPLITTER;\
	DD_AVX_AVX_TYPE sp = DD_AVX_AVX_FUNC(broadcast_sd)(&DD_AVX_SP); \
	DD_AVX_AVX_TYPE one,mi,bh,bl,ch,cl,sh,sl,wh,wl,th,tl,p1,p2,t0,t1,t2,eh,t3; \
	double Htmp[4]={0,0,0,0}; \
   	mi = DD_AVX_AVX_FUNC(set_pd)(-1.0,-1.0,-1.0,-1.0)

/**********************************************************
 *                    Quad x Quad                 *
 **********************************************************/
/**********************************************************
 * ddavx_quad_addn_avx_load(b_hi,b_lo,c_hi,c_lo)            *
 **********************************************************
  (b_hi,b_lo)  (c_hi,c_lo)
 **********************************************************/
#ifndef use_fast_quad_add
#define ddavx_quad_addn_avx_load(b_hi,b_lo,c_hi,c_lo) \
	sh = ddavx_avx_func(set_pd)((b_lo),(b_hi)); \
	bl = ddavx_avx_func(set_pd)((c_lo),(c_hi))
#else
	#define ddavx_quad_addn_avx_load(b_hi,b_lo,c_hi,c_lo) \
 	bh = ddavx_avx_func(loadu_pd)((double*)&(b_hi)); \
	bl = DD_AVX_AVX_FUNC(loadu_pd)((double*)&(b_lo)); \
	ch = DD_AVX_AVX_FUNC(loadu_pd)((double*)&(c_hi)); \
	p2 = DD_AVX_AVX_FUNC(loadu_pd)((double*)&(c_lo))
#endif

/**********************************************************
 * DD_AVX_MULN_AVX_LOAD(b_hi,b_lo,c_hi,c_lo)            *
 **********************************************************
  (b_hi,b_lo)  (c_hi,c_lo)
 **********************************************************/
#define DD_AVX_MULN_AVX_LOAD(b_hi,b_lo,c_hi,c_lo) \
	bh = DD_AVX_AVX_FUNC(loadu_pd)((double*)&(b_hi)); \
	ch = DD_AVX_AVX_FUNC(loadu_pd)((double*)&(c_hi)); \
	bl = DD_AVX_AVX_FUNC(loadu_pd)((double*)&(b_lo)); \
	cl = DD_AVX_AVX_FUNC(loadu_pd)((double*)&(c_lo))

/**********************************************************
 * DD_AVX_FMAN_AVX_LOAD(a_hi,a_lo)                      *
 **********************************************************
  (a_hi,a_lo)
 **********************************************************/
#define DD_AVX_FMAN_AVX_LOAD(a_hi,a_lo) \
	t1  = DD_AVX_AVX_FUNC(sub_pd)(ch,p1); \
	p2  = DD_AVX_AVX_FUNC(sub_pd)(p2,t1); \
	bh  = DD_AVX_AVX_FUNC(loadu_pd)((double*)&(a_hi)); \
	bl  = DD_AVX_AVX_FUNC(loadu_pd)((double*)&(a_lo))

/**********************************************************
 * DD_AVX_SQRN_AVX_LOAD(b_hi,b_lo)                      *
 **********************************************************
  (b_hi,b_lo)
 **********************************************************/
#define DD_AVX_SQRN_AVX_LOAD(b_hi,b_lo) \
	bh = DD_AVX_AVX_FUNC(loadu_pd)((double*)&(b_hi)); \
	bl = DD_AVX_AVX_FUNC(loadu_pd)((double*)&(b_lo))

/**********************************************************
 * DD_AVX_ADDN_AVX_CORE                                 *
 **********************************************************
  (b_hi,b_lo) + (c_hi,c_lo)
 **********************************************************/
#ifndef USE_FAST_QUAD_ADD
	#define DD_AVX_ADDN_AVX_CORE \
		sh = DD_AVX_AVX_FUNC(add_pd)(bh,ch); \
		th = DD_AVX_AVX_FUNC(sub_pd)(sh,bh); \
		t0 = DD_AVX_AVX_FUNC(sub_pd)(sh,th); \
		ch = DD_AVX_AVX_FUNC(sub_pd)(ch,th); \
		bh = DD_AVX_AVX_FUNC(sub_pd)(bh,t0); \
		bh = DD_AVX_AVX_FUNC(add_pd)(bh,ch); \
		sl = DD_AVX_AVX_FUNC(add_pd)(bl,p2); \
		th = DD_AVX_AVX_FUNC(sub_pd)(sl,bl); \
		t0 = DD_AVX_AVX_FUNC(sub_pd)(sl,th); \
		p2 = DD_AVX_AVX_FUNC(sub_pd)(p2,th); \
		bl = DD_AVX_AVX_FUNC(sub_pd)(bl,t0); \
		bl = DD_AVX_AVX_FUNC(add_pd)(bl,p2); \
		bh = DD_AVX_AVX_FUNC(add_pd)(bh,sl); \
		th = sh; \
		th = DD_AVX_AVX_FUNC(add_pd)(th,bh); \
		sh = DD_AVX_AVX_FUNC(sub_pd)(th,sh); \
		bh = DD_AVX_AVX_FUNC(sub_pd)(bh,sh); \
		bh = DD_AVX_AVX_FUNC(add_pd)(bh,bl); \
		sh = DD_AVX_AVX_FUNC(add_pd)(th,bh)
#else
	#define DD_AVX_ADDN_AVX_CORE \
		th = DD_AVX_AVX_FUNC(add_pd)(bh,ch); \
		wh = DD_AVX_AVX_FUNC(sub_pd)(th,bh); \
		t0 = DD_AVX_AVX_FUNC(sub_pd)(th,wh); \
		ch = DD_AVX_AVX_FUNC(sub_pd)(ch,wh); \
		bh = DD_AVX_AVX_FUNC(sub_pd)(bh,t0); \
		bh = DD_AVX_AVX_FUNC(add_pd)(bh,ch); \
		bh = DD_AVX_AVX_FUNC(add_pd)(bh,bl); \
		bh = DD_AVX_AVX_FUNC(add_pd)(bh,p2); \
		sh = DD_AVX_AVX_FUNC(add_pd)(th,bh)
#endif

/**********************************************************
 * DD_AVX_MULN_AVX_CORE  ..mp3                             *
 **********************************************************
  (b_hi,b_lo) x (c_hi,c_lo)
 **********************************************************/
#if USE_AVX2==1
	#define DD_AVX_MULN_AVX_CORE \
		p1 = DD_AVX_AVX_FUNC(mul_pd)(mi,bh); /*FMA*/ \
		p1 = DD_AVX_AVX_FUNC(mul_pd)(p1,ch); /*FMA*/\
		p2 = _mm256_fmadd_pd(bh,ch,p1); /*FMA*/\
		p1 = DD_AVX_AVX_FUNC(mul_pd)(mi,p1); /*FMA*/\
		p2 = _mm256_fmadd_pd(bh,cl,p2); \
		p2 = _mm256_fmadd_pd(bl,ch,p2); \
		ch = DD_AVX_AVX_FUNC(add_pd)(p1,p2)
#else
	#define DD_AVX_MULN_AVX_CORE \
		p1  = DD_AVX_AVX_FUNC(mul_pd)(bh,ch); \
		sh  = DD_AVX_AVX_FUNC(mul_pd)(sp,bh); \
		sl  = DD_AVX_AVX_FUNC(mul_pd)(sp,ch); \
		th  = DD_AVX_AVX_FUNC(sub_pd)(sh,bh); \
		tl  = DD_AVX_AVX_FUNC(sub_pd)(sl,ch); \
		sh  = DD_AVX_AVX_FUNC(sub_pd)(sh,th); \
		sl  = DD_AVX_AVX_FUNC(sub_pd)(sl,tl); \
		t1  = DD_AVX_AVX_FUNC(mul_pd)(bh,cl); \
		wh  = DD_AVX_AVX_FUNC(sub_pd)(bh,sh); \
		t2  = DD_AVX_AVX_FUNC(mul_pd)(ch,bl); \
		wl  = DD_AVX_AVX_FUNC(sub_pd)(ch,sl); \
		t0  = DD_AVX_AVX_FUNC(mul_pd)(wh,wl); \
		p2  = DD_AVX_AVX_FUNC(mul_pd)(sh,sl); \
		sh  = DD_AVX_AVX_FUNC(mul_pd)(sh,wl); \
		sl  = DD_AVX_AVX_FUNC(mul_pd)(sl,wh); \
		p2  = DD_AVX_AVX_FUNC(sub_pd)(p2,p1); \
		p2  = DD_AVX_AVX_FUNC(add_pd)(p2,sh); \
		p2  = DD_AVX_AVX_FUNC(add_pd)(p2,sl); \
		p2  = DD_AVX_AVX_FUNC(add_pd)(p2,t0); \
		p2  = DD_AVX_AVX_FUNC(add_pd)(p2,t1); \
		p2  = DD_AVX_AVX_FUNC(add_pd)(p2,t2); \
		ch  = DD_AVX_AVX_FUNC(add_pd)(p1,p2)
#endif

/**********************************************************
 * DD_AVX_SQRN_AVX_CORE                                 *
 **********************************************************
  (b_hi,b_lo) x (b_hi,b_lo)
 **********************************************************/
#if USE_AVX2==1 
	#define DD_AVX_SQRN_AVX_CORE \
		p1 = DD_AVX_AVX_FUNC(mul_pd)(mi,bh); /*FMA*/ \
		p1 = DD_AVX_AVX_FUNC(mul_pd)(p1,ch); /*FMA*/\
		p2 = _mm256_fmadd_pd(bh,ch,p1); /*FMA*/\
		p1 = DD_AVX_AVX_FUNC(mul_pd)(mi,p1); /*FMA*/\
		p2 = _mm256_fmadd_pd(bh,cl,p2); \
		p2 = _mm256_fmadd_pd(bl,ch,p2); \
		ch = DD_AVX_AVX_FUNC(add_pd)(p1,p2)
#else
	#define DD_AVX_SQRN_AVX_CORE \
		p1  = DD_AVX_AVX_FUNC(mul_pd)(bh,bh); \
		ch  = DD_AVX_AVX_FUNC(mul_pd)(sp,bh); \
		p2  = DD_AVX_AVX_FUNC(sub_pd)(ch,bh); \
		ch  = DD_AVX_AVX_FUNC(sub_pd)(ch,p2); \
		cl  = DD_AVX_AVX_FUNC(sub_pd)(bh,ch); \
		p2  = DD_AVX_AVX_FUNC(mul_pd)(ch,ch); \
		ch  = DD_AVX_AVX_FUNC(add_pd)(ch,ch); \
		ch  = DD_AVX_AVX_FUNC(mul_pd)(ch,cl); \
		cl  = DD_AVX_AVX_FUNC(mul_pd)(cl,cl); \
		p2  = DD_AVX_AVX_FUNC(sub_pd)(p2,p1); \
		p2  = DD_AVX_AVX_FUNC(add_pd)(p2,ch); \
		p2  = DD_AVX_AVX_FUNC(add_pd)(p2,cl); \
		bh  = DD_AVX_AVX_FUNC(add_pd)(bh,bh); \
		bh  = DD_AVX_AVX_FUNC(mul_pd)(bh,bl); \
		bl  = DD_AVX_AVX_FUNC(mul_pd)(bl,bl); \
		p2  = DD_AVX_AVX_FUNC(add_pd)(p2,bh); \
		p2  = DD_AVX_AVX_FUNC(add_pd)(p2,bl); \
		ch  = DD_AVX_AVX_FUNC(add_pd)(p1,p2)
#endif

/**********************************************************
 * DD_AVX_ADDN_AVX_STORE(a_hi,a_lo)                     *
 **********************************************************
  (a_hi,a_lo) <-
 **********************************************************/
#define DD_AVX_ADDN_AVX_STORE(a_hi,a_lo) \
		DD_AVX_AVX_FUNC(storeu_pd)((double*)&(a_hi),sh); \
		sh = DD_AVX_AVX_FUNC(sub_pd)(sh,th); \
		bh = DD_AVX_AVX_FUNC(sub_pd)(bh,sh); \
		DD_AVX_AVX_FUNC(storeu_pd)((double*)&(a_lo),bh)

/**********************************************************
 * DD_AVX_MULN_AVX_STORE(a_hi,a_lo)                     *
 **********************************************************
  (a_hi,a_lo) <-
 **********************************************************/
#define DD_AVX_MULN_AVX_STORE(a_hi,a_lo) \
		DD_AVX_AVX_FUNC(storeu_pd)(&(a_hi),ch); \
		ch  = DD_AVX_AVX_FUNC(sub_pd)(ch,p1); \
		p2  = DD_AVX_AVX_FUNC(sub_pd)(p2,ch); \
		DD_AVX_AVX_FUNC(storeu_pd)(&(a_lo),p2)
#define DD_AVX_MULN_AVX_STOREU(a_hi,a_lo) \
		DD_AVX_AVX_FUNC(storeu_pd)(&(a_hi),ch); \
		ch  = DD_AVX_AVX_FUNC(sub_pd)(ch,p1); \
		p2  = DD_AVX_AVX_FUNC(sub_pd)(p2,ch); \
		DD_AVX_AVX_FUNC(storeu_pd)(&(a_lo),p2)

/**********************************************************
 * DD_AVX_ADDN_AVX(a_hi,a_lo,b_hi,b_lo,c_hi,c_lo)       *
 **********************************************************
  (a_hi,a_lo) <- (b_hi,b_lo) + (c_hi,c_lo)
 **********************************************************/
#define DD_AVX_ADDN_AVX(a_hi,a_lo,b_hi,b_lo,c_hi,c_lo) \
		DD_AVX_ADDN_AVX_LOAD((b_hi),(b_lo),(c_hi),(c_lo)); \
		DD_AVX_ADDN_AVX_CORE; \
		DD_AVX_ADDN_AVX_STORE((a_hi),(a_lo))

/**********************************************************
 * DD_AVX_MULN_AVX(a_hi,a_lo,b_hi,b_lo,c_hi,c_lo)       *
 **********************************************************
  (a_hi,a_lo) <- (b_hi,b_lo) x (c_hi,c_lo)
 **********************************************************/
#define DD_AVX_MULN_AVX(a_hi,a_lo,b_hi,b_lo,c_hi,c_lo) \
		DD_AVX_MULN_AVX_LOAD((b_hi),(b_lo),(c_hi),(c_lo)); \
		DD_AVX_MULN_AVX_CORE; \
		DD_AVX_MULN_AVX_STORE((a_hi),(a_lo))

/**********************************************************
 * DD_AVX_SQRN_AVX(a_hi,a_lo,b_hi,b_lo)                 *
 **********************************************************
  (a_hi,a_lo) <- (b_hi,b_lo) x (b_hi,b_lo)
 **********************************************************/
#define DD_AVX_SQRN_AVX(a_hi,a_lo,b_hi,b_lo) \
		DD_AVX_SQRN_AVX_LOAD((b_hi),(b_lo)); \
		DD_AVX_SQRN_AVX_CORE; \
		DD_AVX_MULN_AVX_STORE((a_hi),(a_lo))

/***************************************************************
 * DD_AVX_FMAN_AVX(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo,c_hi,c_lo)  *
 ***************************************************************
  (d_hi,d_lo) <- (a_hi,a_lo) + (b_hi,b_lo) * (c_hi,c_lo)
 ***************************************************************/
#define DD_AVX_FMAN_AVX(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo,c_hi,c_lo) \
		DD_AVX_MULN_AVX_LOAD((b_hi),(b_lo),(c_hi),(c_lo)); \
		DD_AVX_MULN_AVX_CORE; \
		DD_AVX_FMAN_AVX_LOAD((a_hi),(a_lo)); \
		DD_AVX_ADDN_AVX_CORE; \
		DD_AVX_ADDN_AVX_STORE((d_hi),(d_lo))

/***************************************************************
 * DD_AVX_FMAN_AVX(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo,c_hi,c_lo)  *
 ***************************************************************
  (d_hi,d_lo) <- (a_hi,a_lo) + (b_hi,b_lo) * (c_hi,c_lo)
 ***************************************************************/
#define DD_AVX_FMAN_AVX(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo,c_hi,c_lo) \
		DD_AVX_MULN_AVX_LOAD((b_hi),(b_lo),(c_hi),(c_lo)); \
		DD_AVX_MULN_AVX_CORE; \
		DD_AVX_FMAN_AVX_LOAD((a_hi),(a_lo)); \
		DD_AVX_ADDN_AVX_CORE; \
		DD_AVX_ADDN_AVX_STORE((d_hi),(d_lo))

/***************************************************************
 * DD_AVX_FSAN_AVX(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo)            *
 ***************************************************************
  (d_hi,d_lo) <- (a_hi,a_lo) + (b_hi,b_lo) * (b_hi,b_lo)
 ***************************************************************/
#define DD_AVX_FSAN_AVX(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo) \
		DD_AVX_SQRN_AVX_LOAD((b_hi),(b_lo)); \
		DD_AVX_SQRN_AVX_CORE; \
		DD_AVX_FMAN_AVX_LOAD((a_hi),(a_lo)); \
		DD_AVX_ADDN_AVX_CORE; \
		DD_AVX_ADDN_AVX_STORE((d_hi),(d_lo))

/**********************************************************
 *                                                        *
 *               AVX(Nbit; Double x Quad)                 *
 *                                                        *
 **********************************************************/

/**********************************************************
 * DD_AVX_MULDN_AVX_LOAD(b_hi,b_lo,c)                   *
 **********************************************************
  (b_hi,b_lo)  (c)
 **********************************************************/
#define DD_AVX_MULDN_AVX_LOAD(b_hi,b_lo,c) \
		bh  = DD_AVX_AVX_FUNC(loadu_pd)((double*)&(b_hi)); \
		bl  = DD_AVX_AVX_FUNC(loadu_pd)((double*)&(b_lo)); \
		ch  = DD_AVX_AVX_FUNC(broadcast_sd)((double*)&(c))

/**********************************************************
 * DD_AVX_MULDN_AVX_CORE     .mp3                       *
 **********************************************************
  (b_hi,b_lo) x c (matvec)
 **********************************************************/
#if USE_AVX2==1
	#define DD_AVX_MULDN_AVX_CORE \
		p1 = DD_AVX_AVX_FUNC(mul_pd)(mi,bh); \
		p1 = DD_AVX_AVX_FUNC(mul_pd)(p1,ch); \
		p2 = _mm256_fmadd_pd(bh,ch,p1); \
		p1 = DD_AVX_AVX_FUNC(mul_pd)(mi,p1); \
		p2 = _mm256_fmadd_pd(bl,ch,p2); \
		ch  = DD_AVX_AVX_FUNC(add_pd)(p1,p2)
#else
	#define DD_AVX_MULDN_AVX_CORE \
		p1  = DD_AVX_AVX_FUNC(mul_pd)(bh,ch); \
		bl  = DD_AVX_AVX_FUNC(mul_pd)(bl,ch); \
		sh  = DD_AVX_AVX_FUNC(mul_pd)(sp,bh); \
		th  = DD_AVX_AVX_FUNC(sub_pd)(sh,bh); \
		sh  = DD_AVX_AVX_FUNC(sub_pd)(sh,th); \
		bh  = DD_AVX_AVX_FUNC(sub_pd)(bh,sh); \
		sl  = DD_AVX_AVX_FUNC(mul_pd)(sp,ch); \
		tl  = DD_AVX_AVX_FUNC(sub_pd)(sl,ch); \
		sl  = DD_AVX_AVX_FUNC(sub_pd)(sl,tl); \
		ch  = DD_AVX_AVX_FUNC(sub_pd)(ch,sl); \
		t2  = DD_AVX_AVX_FUNC(mul_pd)(bh,ch); \
		p2  = DD_AVX_AVX_FUNC(mul_pd)(sh,sl); \
		t0  = DD_AVX_AVX_FUNC(mul_pd)(sh,ch); \
		t1  = DD_AVX_AVX_FUNC(mul_pd)(sl,bh); \
		p2  = DD_AVX_AVX_FUNC(sub_pd)(p2,p1); \
		p2  = DD_AVX_AVX_FUNC(add_pd)(p2,t0); \
		p2  = DD_AVX_AVX_FUNC(add_pd)(p2,t1); \
		p2  = DD_AVX_AVX_FUNC(add_pd)(p2,t2); \
		p2  = DD_AVX_AVX_FUNC(add_pd)(p2,bl); \
		ch  = DD_AVX_AVX_FUNC(add_pd)(p1,p2)
#endif

/**********************************************************
 * DD_AVX_MULDN_AVX(a_hi,a_lo,b_hi,b_lo,c)              *
 **********************************************************
  (a_hi,a_lo) <- (b_hi,b_lo) x c
 **********************************************************/
#define DD_AVX_MULDN_AVX(a_hi,a_lo,b_hi,b_lo,c) \
		DD_AVX_MULDN_AVX_LOAD((b_hi),(b_lo),(c)); \
		DD_AVX_MULDN_AVX_CORE; \
		DD_AVX_MULN_AVX_STORE((a_hi),(a_lo))

/***************************************************************************
 * DD_AVX_FMADN_AVX(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo,c)                     *
 * DD_AVX_FMADN_AVX_LDSD(d_hi,d_lo,a_hi,a_lo,b0_hi,b0_lo,b1_hi,b1_lo,c)  *
 ***************************************************************************
  (d_hi,d_lo) <- (a_hi,a_lo) + (b_hi,b_lo) * c
 ***************************************************************/
#define DD_AVX_FMADN_AVX(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo,c) \
		DD_AVX_MULDN_AVX_LOAD((b_hi),(b_lo),(c)); \
		DD_AVX_MULDN_AVX_CORE; \
		DD_AVX_FMAN_AVX_LOAD((a_hi),(a_lo)); \
		DD_AVX_ADDN_AVX_CORE; \
		DD_AVX_ADDN_AVX_STORE((d_hi),(d_lo))

//per vector size operations
//have to implement additional code for new vector size
/**********************************************************
 *                                                        *
 *               AVX(256bit; Quad x Quad)                 *
 *                                                        *
 **********************************************************/

/**********************************************************
 * DD_AVX_FMA4_AVX_LOAD(a_hi,a_lo)                      *
 **********************************************************
  (a_hi,a_lo)
 **********************************************************/
#define DD_AVX_FMA4_AVX_LOAD_SD2(a0_hi,a0_lo) \
	t1  = _mm256_sub_pd(ch,p1); \
	p2  = _mm256_sub_pd(p2,t1); \
	bh  = _mm256_loadu_pd(&(a0_hi)); \
	bl  = _mm256_loadu_pd(&(a0_lo))

////////////////////////////////////////////////////////////
#define DD_AVX_FMA4_AVX_LOAD_SD(a0_hi,a0_lo,a1_hi,a1_lo,a2_hi,a2_lo,a3_hi,a3_lo) \
	t1  = _mm256_sub_pd(ch,p1); \
	p2  = _mm256_sub_pd(p2,t1); \
	bh  = _mm256_set_pd((a3_hi),(a2_hi),(a1_hi),(a0_hi)); \
	bl  = _mm256_set_pd((a3_lo),(a2_lo),(a1_lo),(a0_lo))

/**********************************************************
 * DD_AVX_ADD4_AVX_STORE(a_hi,a_lo)                     *
 **********************************************************
  (a_hi,a_lo) <-
 **********************************************************/
#define DD_AVX_ADD4_AVX_STORE_SD2(a0_hi,a0_lo) \
	_mm256_stream_pd(&(a0_hi), sh); \
	sh = _mm256_sub_pd(sh,th); \
	bh = _mm256_sub_pd(bh,sh); \
	_mm256_stream_pd(&(a0_lo), bh)

////////////////////////////////////////////////////////////////
#define DD_AVX_ADD4_AVX_STORE_SD(a0_hi,a0_lo,a1_hi,a1_lo,a2_hi,a2_lo,a3_hi,a3_lo) \
	*(__m128d*)&t3 = _mm256_extractf128_pd(sh, 1); \
	_mm_storel_pd(&(a0_hi), *(__m128d*)&sh); \
	_mm_storeh_pd(&(a1_hi), *(__m128d*)&sh); \
	_mm_storel_pd(&(a2_hi), *(__m128d*)&t3); \
	_mm_storeh_pd(&(a3_hi), *(__m128d*)&t3); \
	sh = _mm256_sub_pd(sh,th); \
	bh = _mm256_sub_pd(bh,sh); \
	*(__m128d*)&t3 = _mm256_extractf128_pd(bh, 1); \
	_mm_storel_pd(&(a0_lo), *(__m128d*)&bh); \
	_mm_storeh_pd(&(a1_lo), *(__m128d*)&bh); \
	_mm_storel_pd(&(a2_lo), *(__m128d*)&t3); \
	_mm_storeh_pd(&(a3_lo), *(__m128d*)&t3)

/**********************************************************
 *                                                        *
 *              AVX(256bit; Double x Quad)                *
 *                                                        *
 **********************************************************/
/**********************************************************
 * DD_AVX_MULD4_AVX_LOAD(b_hi,b_lo,c)                   *
 **********************************************************
  (b_hi,b_lo)  (c)
 **********************************************************/
#define DD_AVX_MULD4_AVX_LOAD_SD2(b0_hi,b0_lo,c) \
	bh  = _mm256_broadcast_sd((double*)&(b0_hi)); \
	bl  = _mm256_broadcast_sd((double*)&(b0_lo)); \
	ch  = _mm256_loadu_pd(&(c))

////////////////////////////////////////////////////////////////////
#define DD_AVX_MULD4_AVX_LOAD_SD(b0_hi,b0_lo,b1_hi,b1_lo,b2_hi,b2_lo,b3_hi,b3_lo,c) \
	bh  = _mm256_set_pd((b3_hi),(b2_hi),(b1_hi),(b0_hi)); \
	bl  = _mm256_set_pd((b3_lo),(b2_lo),(b1_lo),(b0_lo)); \
	ch  = _mm256_loadu_pd(&(c))

/***************************************************************************
 * DD_AVX_FMAD4_AVX_LDSD(d_hi,d_lo,a_hi,a_lo,b0_hi,b0_lo,b1_hi,b1_lo,c)  *
 ***************************************************************************
  (d_hi,d_lo) <- (a_hi,a_lo) + (b_hi,b_lo) * c
 ***************************************************************/
#define DD_AVX_FMAD4_AVX_LDSD(d_hi,d_lo,a_hi,a_lo,b0_hi,b0_lo,b1_hi,b1_lo,b2_hi,b2_lo,b3_hi,b3_lo,c) \
	DD_AVX_MULD4_AVX_LOAD_SD((b0_hi),(b0_lo),(b1_hi),(b1_lo),(b2_hi),(b2_lo),(b3_hi),(b3_lo),(c)); \
	DD_AVX_MULDN_AVX_CORE; \
	DD_AVX_FMAN_AVX_LOAD((a_hi),(a_lo)); \
	DD_AVX_ADDN_AVX_CORE; \
	DD_AVX_ADDN_AVX_STORE((d_hi),(d_lo))

#if USE_AVX2==1 
	#define DD_AVX_DOUBLE_FMA4_AVX_LDSD(d_hi,a_hi,b0_hi,b1_hi,b2_hi,b3_hi,c) \
		bl = _mm256_load_pd(&(c)); \
		ch = _mm256_set_pd((b0_hi),(b1_hi),(b2_hi),(b3_hi)); \
		d_hi = _mm256_fmadd_pd(bl,ch,d_hi);
#else
	#define DD_AVX_DOUBLE_FMA4_AVX_LDSD(d_hi,a_hi,b0_hi,b1_hi,b2_hi,b3_hi,c) \
		bl = _mm256_load_pd(&(c)); \
		ch = _mm256_set_pd((b0_hi),(b1_hi),(b2_hi),(b3_hi)); \
		bl = _mm256_mul_pd(bl,ch); \
		d_hi = _mm256_add_pd(d_hi,bl); 
#endif

/****************************************************************/
#define DD_AVX_FMAD4_AVX_STSD(d0_hi,d0_lo,d1_hi,d1_lo,d2_hi,d2_lo,d3_hi,d3_lo,a0_hi,a0_lo,a1_hi,a1_lo,a2_hi,a2_lo,a3_hi,a3_lo,b0_hi,b0_lo,b1_hi,b1_lo,b2_hi,b2_lo,b3_hi,b3_lo,c) \
	DD_AVX_MULD4_AVX_LOAD_SD2((b0_hi),(b0_lo),(c)); \
	DD_AVX_MULDN_AVX_CORE; \
	DD_AVX_FMA4_AVX_LOAD_SD((a0_hi),(a0_lo),(a1_hi),(a1_lo),(a2_hi),(a2_lo),(a3_hi),(a3_lo)); \
	DD_AVX_ADDN_AVX_CORE; \
	DD_AVX_ADD4_AVX_STORE_SD((d0_hi),(d0_lo),(d1_hi),(d1_lo),(d2_hi),(d2_lo),(d3_hi),(d3_lo))
	
	////////////////////////////////////////////////////////////////////
#define DD_AVX_FMAD4_AVX_STSD2(d0_hi,d0_lo,a0_hi,a0_lo,b0_hi,b0_lo,c) \
	DD_AVX_MULD4_AVX_LOAD_SD2((b0_hi),(b0_lo),(c)); \
	DD_AVX_MULDN_AVX_CORE; \
	DD_AVX_FMA4_AVX_LOAD_SD2((a0_hi),(a0_lo)); \
	DD_AVX_ADDN_AVX_CORE; \
	DD_AVX_ADD4_AVX_STORE_SD2((d0_hi),(d0_lo))
	
	/////////////////////////////////////////////////////////////////////
#define DD_AVX_FMAD4_AVX_STSD3(d0_hi,d0_lo,d1_hi,d1_lo,d2_hi,d2_lo,d3_hi,d3_lo,a0_hi,a0_lo,a1_hi,a1_lo,a2_hi,a2_lo,a3_hi,a3_lo,b0_hi,b0_lo,c) \
	DD_AVX_MULD4_AVX_LOAD_SD2((b0_hi),(b0_lo),(c)); \
	DD_AVX_MULDN_AVX_CORE; \
	DD_AVX_FMA4_AVX_LOAD_SD((a0_hi),(a0_lo),(a1_hi),(a1_lo),(a2_hi),(a2_lo),(a3_hi),(a3_lo)); \
	DD_AVX_ADDN_AVX_CORE; \
	DD_AVX_ADD4_AVX_STORE_SD((d0_hi),(d0_lo),(d1_hi),(d1_lo),(d2_hi),(d2_lo),(d3_hi),(d3_lo))

/**********************************************************
 *                                                        *
 *                      SSE2(SD)                          *
 *                                                        *
 **********************************************************/
/**********************************************************
 * DD_AVX_MUL_SSE2_STORE(a_hi,a_lo)                     *
 **********************************************************
  (a_hi,a_lo) <-
 **********************************************************/
#define DD_AVX_MUL_SSE2_STORE(a_hi,a_lo) \
	_mm_store_sd(&(a_hi),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(sh)  = _mm_sub_sd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(wh)  = _mm_sub_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(sh)); \
	_mm_store_sd(&(a_lo),DD_AVX_VEC_CAST(wh))
/**********************************************************
 * DD_AVX_ADD_SSE2_LOAD(b_hi,b_lo,c_hi,c_lo)            *
 **********************************************************
  (b_hi,b_lo)  (c_hi,c_lo)
 **********************************************************/
#ifndef USE_FAST_QUAD_ADD
#define DD_AVX_ADD_SSE2_LOAD(b_hi,b_lo,c_hi,c_lo) \
	DD_AVX_VEC_CAST(sh) = _mm_set_pd((b_lo),(b_hi)); \
	DD_AVX_VEC_CAST(bl) = _mm_set_pd((c_lo),(c_hi))
#else
#define DD_AVX_ADD_SSE2_LOAD(b_hi,b_lo,c_hi,c_lo) \
	DD_AVX_VEC_CAST(eh) = _mm_set_sd((b_hi)); \
	DD_AVX_VEC_CAST(cl) = _mm_set_sd((b_lo)); \
	DD_AVX_VEC_CAST(sh) = _mm_set_sd((c_hi)); \
	DD_AVX_VEC_CAST(wh) = _mm_set_sd((c_lo))
#endif
/**********************************************************
 * DD_AVX_FMA_SSE2_LOAD(a_hi,a_lo)                      *
 **********************************************************
  (a_hi,a_lo)
 **********************************************************/
#ifndef USE_FAST_QUAD_ADD
#define DD_AVX_FMA_SSE2_LOAD(a_hi,a_lo) \
	DD_AVX_VEC_CAST(th)  = _mm_sub_sd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(wh)  = _mm_sub_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(bl)  = _mm_set_pd((a_lo),(a_hi)); \
	DD_AVX_VEC_CAST(sh)  = _mm_unpacklo_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(wh))
#else
#define DD_AVX_FMA_SSE2_LOAD(a_hi,a_lo) \
	DD_AVX_VEC_CAST(th)  = _mm_sub_sd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(wh)  = _mm_sub_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(eh) = _mm_set_sd((a_hi)); \
	DD_AVX_VEC_CAST(cl) = _mm_set_sd((a_lo))
#endif
/**********************************************************
 * DD_AVX_MUL_SSE2_CORE(b_hi,b_lo,c_hi,c_lo)            *
 **********************************************************
  (b_hi,b_lo) x (c_hi,c_lo)
 **********************************************************/
#define DD_AVX_MUL_SSE2_CORE(b_hi,b_lo,c_hi,c_lo) \
	DD_AVX_VEC_CAST(sh)  = _mm_set_pd(SPLITTER,SPLITTER); \
	DD_AVX_VEC_CAST(ch) = _mm_set_pd((c_hi),(b_hi)); \
	DD_AVX_VEC_CAST(bh)  = _mm_unpackhi_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(tl) = _mm_set_pd((b_lo),(c_lo)); \
	DD_AVX_VEC_CAST(bh)  = _mm_mul_sd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(sh)  = _mm_mul_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(th)  = _mm_sub_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(sh)  = _mm_sub_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(th)  = _mm_mul_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(tl)); \
	DD_AVX_VEC_CAST(ch) = _mm_sub_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(eh)  = _mm_unpackhi_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(wh)  = _mm_unpacklo_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(ch) = _mm_unpackhi_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(wh));  \
	DD_AVX_VEC_CAST(wh)  = _mm_mul_pd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(eh)); \
	DD_AVX_VEC_CAST(sh)  = _mm_mul_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(ch) = _mm_unpackhi_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(tl) = _mm_unpackhi_pd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(wh)); \
	DD_AVX_VEC_CAST(eh)  = _mm_unpackhi_pd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(wh)  = _mm_sub_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(wh)  = _mm_add_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(wh)  = _mm_add_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(wh)  = _mm_add_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(tl)); \
	DD_AVX_VEC_CAST(wh)  = _mm_add_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(eh)); \
	DD_AVX_VEC_CAST(wh)  = _mm_add_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(sh)  = _mm_add_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(bh))
/**********************************************************
 * DD_AVX_MULD_SSE2_CORE(b_hi,b_lo,c)                   *
 **********************************************************
  (b_hi,b_lo) x c
 **********************************************************/
#define DD_AVX_MULD_SSE2_CORE(b_hi,b_lo,c) \
	DD_AVX_VEC_CAST(sh)  = _mm_set_pd(SPLITTER,SPLITTER); \
	DD_AVX_VEC_CAST(ch) = _mm_set_pd((b_hi),(c)); \
	DD_AVX_VEC_CAST(bh)  = _mm_unpackhi_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(sl) = _mm_load_sd(&(b_lo)); \
	DD_AVX_VEC_CAST(bh)  = _mm_mul_sd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(sl) = _mm_mul_sd(DD_AVX_VEC_CAST(sl),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(sh)  = _mm_mul_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(th)  = _mm_sub_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(sh)  = _mm_sub_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(ch) = _mm_sub_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(t1)  = _mm_unpackhi_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(wh)  = _mm_unpacklo_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(ch) = _mm_unpackhi_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(wh));  \
	DD_AVX_VEC_CAST(wh)  = _mm_mul_pd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(t1)); \
	DD_AVX_VEC_CAST(sh)  = _mm_mul_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(ch) = _mm_unpackhi_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(th)  = _mm_unpackhi_pd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(wh)); \
	DD_AVX_VEC_CAST(wh)  = _mm_sub_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(wh)  = _mm_add_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(wh)  = _mm_add_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(wh)  = _mm_add_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(wh)  = _mm_add_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(sl)); \
	DD_AVX_VEC_CAST(sh)  = _mm_add_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(bh))
/**********************************************************
 * DD_AVX_SQR_SSE2_CORE(b_hi,b_lo)                      *
 **********************************************************
  (b_hi,b_lo) x (b_hi,b_lo)
 **********************************************************/
#define DD_AVX_SQR_SSE2_CORE(b_hi,b_lo) \
	DD_AVX_VEC_CAST(sh)  = _mm_set_sd(SPLITTER); \
	DD_AVX_VEC_CAST(th)  = _mm_load_sd(&(b_hi)); \
	DD_AVX_VEC_CAST(bl)  = _mm_load_sd(&(b_lo)); \
	DD_AVX_VEC_CAST(bh)  = _mm_mul_sd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(sh)  = _mm_mul_sd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(wh)  = _mm_sub_sd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(sh)  = _mm_sub_sd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(wh)); \
	DD_AVX_VEC_CAST(cl)  = _mm_sub_sd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(wh)  = _mm_mul_sd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(sh)  = _mm_add_sd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(sh)  = _mm_mul_sd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(cl)); \
	DD_AVX_VEC_CAST(cl)  = _mm_mul_sd(DD_AVX_VEC_CAST(cl),DD_AVX_VEC_CAST(cl)); \
	DD_AVX_VEC_CAST(wh)  = _mm_sub_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(wh)  = _mm_add_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(wh)  = _mm_add_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(cl)); \
	DD_AVX_VEC_CAST(th)  = _mm_add_sd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(th)  = _mm_mul_sd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(bl)); \
	DD_AVX_VEC_CAST(bl)  = _mm_mul_sd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(bl)); \
	DD_AVX_VEC_CAST(wh)  = _mm_add_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(wh)  = _mm_add_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(bl)); \
	DD_AVX_VEC_CAST(sh)  = _mm_add_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(bh))
/**********************************************************
 * DD_AVX_ADD_SSE2_CORE(a_hi,a_lo)                      *
 **********************************************************
  (a_hi,a_lo) <- (b_hi,b_lo) + (c_hi,c_lo)
 **********************************************************/
#ifndef USE_FAST_QUAD_ADD
#define DD_AVX_ADD_SSE2_CORE(a_hi,a_lo) \
	DD_AVX_VEC_CAST(t0) = _mm_add_pd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(eh) = _mm_sub_pd(DD_AVX_VEC_CAST(t0),DD_AVX_VEC_CAST(bl)); \
	DD_AVX_VEC_CAST(th) = _mm_sub_pd(DD_AVX_VEC_CAST(t0),DD_AVX_VEC_CAST(eh)); \
	DD_AVX_VEC_CAST(sh) = _mm_sub_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(eh)); \
	DD_AVX_VEC_CAST(bl) = _mm_sub_pd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(bl) = _mm_add_pd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(eh) = _mm_unpackhi_pd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(bl)); \
	DD_AVX_VEC_CAST(sh) = _mm_unpackhi_pd(DD_AVX_VEC_CAST(t0),DD_AVX_VEC_CAST(t0)); \
	DD_AVX_VEC_CAST(th) = DD_AVX_VEC_CAST(t0); \
	DD_AVX_VEC_CAST(bl) = _mm_add_sd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(th) = _mm_add_sd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(bl)); \
	DD_AVX_VEC_CAST(t0) = _mm_sub_sd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(t0)); \
	DD_AVX_VEC_CAST(bl) = _mm_sub_sd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(t0)); \
	DD_AVX_VEC_CAST(bl) = _mm_add_sd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(eh)); \
	DD_AVX_VEC_CAST(sh) = _mm_add_sd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(bl)); \
	_mm_store_sd(&(a_hi),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(sh) = _mm_sub_sd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(bl) = _mm_sub_sd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(sh)); \
	_mm_store_sd(&(a_lo),DD_AVX_VEC_CAST(bl))
#else
#define DD_AVX_ADD_SSE2_CORE(a_hi,a_lo) \
	DD_AVX_VEC_CAST(bl) = _mm_add_sd(DD_AVX_VEC_CAST(eh),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(th) = _mm_sub_sd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(eh)); \
	DD_AVX_VEC_CAST(t0) = _mm_sub_sd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(sh) = _mm_sub_sd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(eh) = _mm_sub_sd(DD_AVX_VEC_CAST(eh),DD_AVX_VEC_CAST(t0)); \
	DD_AVX_VEC_CAST(eh) = _mm_add_sd(DD_AVX_VEC_CAST(eh),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(eh) = _mm_add_sd(DD_AVX_VEC_CAST(eh),DD_AVX_VEC_CAST(cl)); \
	DD_AVX_VEC_CAST(eh) = _mm_add_sd(DD_AVX_VEC_CAST(eh),DD_AVX_VEC_CAST(wh)); \
	DD_AVX_VEC_CAST(th) = _mm_add_sd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(eh)); \
	_mm_store_sd(&(a_hi),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(th) = _mm_sub_sd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(bl)); \
	DD_AVX_VEC_CAST(eh) = _mm_sub_sd(DD_AVX_VEC_CAST(eh),DD_AVX_VEC_CAST(th)); \
	_mm_store_sd(&(a_lo),DD_AVX_VEC_CAST(eh))
#endif
/**********************************************************
 * DD_AVX_MUL_SSE2(a_hi,a_lo,b_hi,b_lo,c_hi,c_lo)       *
 **********************************************************
  (a_hi,a_lo) <- (b_hi,b_lo) x (c_hi,c_lo)
 **********************************************************/
#define DD_AVX_MUL_SSE2(a_hi,a_lo,b_hi,b_lo,c_hi,c_lo) \
	DD_AVX_MUL_SSE2_CORE((b_hi),(b_lo),(c_hi),(c_lo)); \
	DD_AVX_MUL_SSE2_STORE((a_hi),(a_lo))
/**********************************************************
 * DD_AVX_MULD_SSE2(a_hi,a_lo,b_hi,b_lo,c)              *
 **********************************************************
  (a_hi,a_lo) <- (b_hi,b_lo) x c
 **********************************************************/
#define DD_AVX_MULD_SSE2(a_hi,a_lo,b_hi,b_lo,c) \
	DD_AVX_MULD_SSE2_CORE((b_hi),(b_lo),(c)); \
	DD_AVX_MUL_SSE2_STORE((a_hi),(a_lo))
/**********************************************************
 * DD_AVX_SQR_SSE2(a_hi,a_lo,b_hi,b_lo)                 *
 **********************************************************
  (a_hi,a_lo) <- (b_hi,b_lo) x (b_hi,b_lo)
 **********************************************************/
#define DD_AVX_SQR_SSE2(a_hi,a_lo,b_hi,b_lo) \
	DD_AVX_SQR_SSE2_CORE((b_hi),(b_lo)); \
	DD_AVX_MUL_SSE2_STORE((a_hi),(a_lo))
/**********************************************************
 * DD_AVX_ADD_SSE2(a_hi,a_lo,b_hi,b_lo,c_hi,c_lo)       *
 **********************************************************
  (a_hi,a_lo) <- (b_hi,b_lo) + (c_hi,c_lo)
 **********************************************************/
#define DD_AVX_ADD_SSE2(a_hi,a_lo,b_hi,b_lo,c_hi,c_lo) \
	DD_AVX_ADD_SSE2_LOAD((b_hi),(b_lo),(c_hi),(c_lo)); \
	DD_AVX_ADD_SSE2_CORE((a_hi),(a_lo))
/**********************************************************
 * DD_AVX_DIV_SSE2(a_hi,a_lo,b_hi,b_lo,c_hi,c_lo)       *
 **********************************************************
  (a_hi,a_lo) <- (b_hi,b_lo) / (c_hi,c_lo)
 **********************************************************/
#define DD_AVX_DIV_SSE2(a_hi,a_lo,b_hi,b_lo,c_hi,c_lo) \
	DD_AVX_VEC_CAST(sh)  = _mm_set_pd(SPLITTER,SPLITTER); \
	DD_AVX_VEC_CAST(bh)  = _mm_set_pd((b_lo),(b_hi)); \
	DD_AVX_VEC_CAST(ch)  = _mm_set_pd((c_lo),(c_hi)); \
	DD_AVX_VEC_CAST(p2)  = DD_AVX_VEC_CAST(bh); \
	DD_AVX_VEC_CAST(wh)  = DD_AVX_VEC_CAST(ch); \
	DD_AVX_VEC_CAST(p2)  = _mm_div_sd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(wh)  = _mm_unpacklo_pd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(p2)); \
	DD_AVX_VEC_CAST(ch)  = _mm_move_sd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(p2)); \
	DD_AVX_VEC_CAST(p2)  = DD_AVX_VEC_CAST(wh); \
	DD_AVX_VEC_CAST(sh)  = _mm_mul_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(wh)); \
	DD_AVX_VEC_CAST(th)  = _mm_sub_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(wh)); \
	DD_AVX_VEC_CAST(sh)  = _mm_sub_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(ch)  = _mm_mul_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(wh)); \
	DD_AVX_VEC_CAST(wh)  = _mm_sub_pd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(th)  = DD_AVX_VEC_CAST(sh); \
	DD_AVX_VEC_CAST(p1)  = DD_AVX_VEC_CAST(wh); \
	DD_AVX_VEC_CAST(th)  = _mm_unpackhi_pd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(p1)  = _mm_unpackhi_pd(DD_AVX_VEC_CAST(p1),DD_AVX_VEC_CAST(p1)); \
	DD_AVX_VEC_CAST(eh)  = DD_AVX_VEC_CAST(th); \
	DD_AVX_VEC_CAST(th)  = _mm_mul_sd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(wh)); \
	DD_AVX_VEC_CAST(eh)  = _mm_mul_sd(DD_AVX_VEC_CAST(eh),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(wh)  = _mm_mul_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(p1)); \
	DD_AVX_VEC_CAST(sh)  = _mm_mul_sd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(p1)); \
	DD_AVX_VEC_CAST(p1)  = DD_AVX_VEC_CAST(ch); \
	DD_AVX_VEC_CAST(p1)  = _mm_unpackhi_pd(DD_AVX_VEC_CAST(p1),DD_AVX_VEC_CAST(p1)); \
	DD_AVX_VEC_CAST(eh)  = _mm_sub_sd(DD_AVX_VEC_CAST(eh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(eh)  = _mm_add_sd(DD_AVX_VEC_CAST(eh),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(eh)  = _mm_add_sd(DD_AVX_VEC_CAST(eh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(eh)  = _mm_add_sd(DD_AVX_VEC_CAST(eh),DD_AVX_VEC_CAST(wh)); \
	DD_AVX_VEC_CAST(eh)  = _mm_add_sd(DD_AVX_VEC_CAST(eh),DD_AVX_VEC_CAST(p1)); \
	DD_AVX_VEC_CAST(p1)  = DD_AVX_VEC_CAST(ch); \
	DD_AVX_VEC_CAST(p1)  = _mm_add_sd(DD_AVX_VEC_CAST(p1),DD_AVX_VEC_CAST(eh)); \
	DD_AVX_VEC_CAST(wh)  = DD_AVX_VEC_CAST(p1); \
	DD_AVX_VEC_CAST(wh)  = _mm_sub_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(sh)  = DD_AVX_VEC_CAST(bh); \
	DD_AVX_VEC_CAST(sh)  = _mm_sub_sd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(p1)); \
	DD_AVX_VEC_CAST(eh)  = _mm_sub_sd(DD_AVX_VEC_CAST(eh),DD_AVX_VEC_CAST(wh)); \
	DD_AVX_VEC_CAST(th)  = DD_AVX_VEC_CAST(sh); \
	DD_AVX_VEC_CAST(th)  = _mm_sub_sd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(p1)  = _mm_add_sd(DD_AVX_VEC_CAST(p1),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(wh)  = DD_AVX_VEC_CAST(sh); \
	DD_AVX_VEC_CAST(wh)  = _mm_sub_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(th)  = DD_AVX_VEC_CAST(bh); \
	DD_AVX_VEC_CAST(th)  = _mm_unpackhi_pd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(bh)  = _mm_sub_sd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(wh)); \
	DD_AVX_VEC_CAST(bh)  = _mm_sub_sd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(p1)); \
	DD_AVX_VEC_CAST(bh)  = _mm_sub_sd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(eh)); \
	DD_AVX_VEC_CAST(bh)  = _mm_add_sd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(th)  = DD_AVX_VEC_CAST(p2); \
	DD_AVX_VEC_CAST(th)  = _mm_unpackhi_pd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(eh)  = DD_AVX_VEC_CAST(th); \
	DD_AVX_VEC_CAST(sh)  = _mm_add_sd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(sh)  = _mm_div_sd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(p2)); \
	DD_AVX_VEC_CAST(th)  = _mm_add_sd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(sh)); \
	_mm_store_sd(&(a_hi),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(th)  = _mm_sub_sd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(eh)); \
	DD_AVX_VEC_CAST(sh)  = _mm_sub_sd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(th)); \
	_mm_store_sd(&(a_lo),DD_AVX_VEC_CAST(sh))
/**********************************************************
 * DD_AVX_SQRT_SSE2(a_hi,a_lo,b_hi,b_lo)                *
 **********************************************************
  (a_hi,a_lo) <- SQRT( (b_hi,b_lo) )
 **********************************************************/
#define DD_AVX_SQRT_SSE2(a_hi,a_lo,b_hi,b_lo) \
	if( (b_hi)==0 ) \
	{ \
		(a_hi) = (a_lo) = 0.0; \
		abort(); \
	} \
	if( (b_hi)<0 ) \
	{ \
		printf("ERROR DD_AVX_VEC_CAST(bh)=%e\n",(b_hi)); \
		(a_hi) = (a_lo) = 0.0; \
		abort(); \
	} \
	DD_AVX_VEC_CAST(wh)  = _mm_set_sd(SPLITTER); \
	DD_AVX_VEC_CAST(bh) = _mm_load_pd(&(b_hi)); \
	DD_AVX_VEC_CAST(bh) = DD_AVX_VEC_CAST(bh); \
	DD_AVX_VEC_CAST(t0) = _mm_set_sd(1.0); \
	DD_AVX_VEC_CAST(t1) = _mm_set_sd(0.5); \
	DD_AVX_VEC_CAST(t2) = _mm_sqrt_pd(DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(t0) = _mm_div_sd(DD_AVX_VEC_CAST(t0),DD_AVX_VEC_CAST(t2)); \
	DD_AVX_VEC_CAST(t2) = _mm_mul_sd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(t0)); \
	DD_AVX_VEC_CAST(t0) = _mm_mul_sd(DD_AVX_VEC_CAST(t0),DD_AVX_VEC_CAST(t1)); \
	DD_AVX_VEC_CAST(p1)  = _mm_mul_sd(DD_AVX_VEC_CAST(t2),DD_AVX_VEC_CAST(t2)); \
	DD_AVX_VEC_CAST(wh)  = _mm_mul_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(t2)); \
	DD_AVX_VEC_CAST(t1)  = _mm_sub_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(t2)); \
	DD_AVX_VEC_CAST(wh)  = _mm_sub_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(t1)); \
	DD_AVX_VEC_CAST(wl)  = _mm_sub_sd(DD_AVX_VEC_CAST(t2),DD_AVX_VEC_CAST(wh)); \
	DD_AVX_VEC_CAST(t1)  = _mm_mul_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(wh)); \
	DD_AVX_VEC_CAST(wh)  = _mm_add_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(wh)); \
	DD_AVX_VEC_CAST(wh)  = _mm_mul_sd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(wl)); \
	DD_AVX_VEC_CAST(wl)  = _mm_mul_sd(DD_AVX_VEC_CAST(wl),DD_AVX_VEC_CAST(wl)); \
	DD_AVX_VEC_CAST(t1)  = _mm_sub_sd(DD_AVX_VEC_CAST(t1),DD_AVX_VEC_CAST(p1)); \
	DD_AVX_VEC_CAST(t1)  = _mm_add_sd(DD_AVX_VEC_CAST(t1),DD_AVX_VEC_CAST(wh)); \
	DD_AVX_VEC_CAST(t1)  = _mm_add_sd(DD_AVX_VEC_CAST(t1),DD_AVX_VEC_CAST(wl)); \
	DD_AVX_VEC_CAST(p1) = _mm_unpacklo_pd(DD_AVX_VEC_CAST(p1),DD_AVX_VEC_CAST(t1)); \
	DD_AVX_VEC_CAST(sh) = _mm_sub_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(p1)); \
	DD_AVX_VEC_CAST(eh) = _mm_sub_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(th) = _mm_sub_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(eh)); \
	DD_AVX_VEC_CAST(p1) = _mm_add_pd(DD_AVX_VEC_CAST(p1),DD_AVX_VEC_CAST(eh)); \
	DD_AVX_VEC_CAST(bh) = _mm_sub_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(bh) = _mm_sub_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(p1)); \
	DD_AVX_VEC_CAST(eh) = _mm_unpackhi_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(ch) = _mm_unpackhi_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(th) = DD_AVX_VEC_CAST(sh); \
	DD_AVX_VEC_CAST(bh) = _mm_add_sd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(th) = _mm_add_sd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(sh) = _mm_sub_sd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(bh) = _mm_sub_sd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(bh) = _mm_add_sd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(eh)); \
	DD_AVX_VEC_CAST(th) = _mm_add_sd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(t0) = _mm_mul_sd(DD_AVX_VEC_CAST(t0),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(p1) = _mm_add_sd(DD_AVX_VEC_CAST(t2),DD_AVX_VEC_CAST(t0)); \
	_mm_store_sd(&(a_hi),DD_AVX_VEC_CAST(p1)); \
	DD_AVX_VEC_CAST(p1) = _mm_sub_sd(DD_AVX_VEC_CAST(p1),DD_AVX_VEC_CAST(t2)); \
	DD_AVX_VEC_CAST(t0) = _mm_sub_sd(DD_AVX_VEC_CAST(t0),DD_AVX_VEC_CAST(p1)); \
	_mm_store_sd(&(a_lo),DD_AVX_VEC_CAST(t0))
/***************************************************************
 * DD_AVX_FMA_SSE2(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo,c_hi,c_lo)  *
 ***************************************************************
  (d_hi,d_lo) <- (a_hi,a_lo) + (b_hi,b_lo) * (c_hi,c_lo)
 ***************************************************************/
#define DD_AVX_FMA_SSE2(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo,c_hi,c_lo) \
	DD_AVX_MUL_SSE2_CORE((b_hi),(b_lo),(c_hi),(c_lo)); \
	DD_AVX_FMA_SSE2_LOAD((a_hi),(a_lo)); \
	DD_AVX_ADD_SSE2_CORE((d_hi),(d_lo))
/***************************************************************
 * DD_AVX_FMAD_SSE2(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo,c)         *
 ***************************************************************
  (d_hi,d_lo) <- (a_hi,a_lo) + (b_hi,b_lo) * c
 ***************************************************************/
#define DD_AVX_FMAD_SSE2(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo,c) \
	DD_AVX_MULD_SSE2_CORE((b_hi),(b_lo),(c)); \
	DD_AVX_FMA_SSE2_LOAD((a_hi),(a_lo)); \
	DD_AVX_ADD_SSE2_CORE((d_hi),(d_lo))
/***************************************************************
 * DD_AVX_FSA_SSE2(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo)            *
 ***************************************************************
  (d_hi,d_lo) <- (a_hi,a_lo) + (b_hi,b_lo) * (b_hi,b_lo)
 ***************************************************************/
#define DD_AVX_FSA_SSE2(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo) \
	DD_AVX_SQR_SSE2_CORE((b_hi),(b_lo)); \
	DD_AVX_FMA_SSE2_LOAD((a_hi),(a_lo)); \
	DD_AVX_ADD_SSE2_CORE((d_hi),(d_lo))
#endif
	/**********************************************************
	 * DD_AVX_HADDALL_AVX(a_hi,a_lo,b_hi,b_lo)              *
	 **********************************************************
	  (a_hi,a_lo) <- sum(i = 0 to 3, (b_hi, b_lo)[i])
	 **********************************************************/
#define DD_AVX_HADDALL_AVX(a_hi, a_lo, b_hi, b_lo) \
	bh = DD_AVX_AVX_FUNC(loadu_pd)((double*)&(b_hi)); \
	bl = DD_AVX_AVX_FUNC(loadu_pd)((double*)&(b_lo)); \
	DD_AVX_VEC_CAST(ch) = _mm256_extractf128_pd(bh, 1); \
	DD_AVX_VEC_CAST(p2) = _mm256_extractf128_pd(bl, 1); \
	DD_AVX_ADD2_SSE2_CORE; \
	DD_AVX_VEC_CAST(eh) = _mm_unpackhi_pd(DD_AVX_VEC_CAST(sh), DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(t0) = _mm_sub_pd(DD_AVX_VEC_CAST(sh), DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(wh) = _mm_sub_pd(DD_AVX_VEC_CAST(bh), DD_AVX_VEC_CAST(t0)); \
	DD_AVX_VEC_CAST(cl) = _mm_unpackhi_pd(DD_AVX_VEC_CAST(wh), DD_AVX_VEC_CAST(wh)); \
	DD_AVX_ADD_SSE2_CORE((a_hi), (a_lo));



#define DD_AVX_ADD_SSE2_CORE(a_hi,a_lo) \
	DD_AVX_VEC_CAST(t0) = _mm_add_pd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(eh) = _mm_sub_pd(DD_AVX_VEC_CAST(t0),DD_AVX_VEC_CAST(bl)); \
	DD_AVX_VEC_CAST(th) = _mm_sub_pd(DD_AVX_VEC_CAST(t0),DD_AVX_VEC_CAST(eh)); \
	DD_AVX_VEC_CAST(sh) = _mm_sub_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(eh)); \
	DD_AVX_VEC_CAST(bl) = _mm_sub_pd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(bl) = _mm_add_pd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(eh) = _mm_unpackhi_pd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(bl)); \
	DD_AVX_VEC_CAST(sh) = _mm_unpackhi_pd(DD_AVX_VEC_CAST(t0),DD_AVX_VEC_CAST(t0)); \
	DD_AVX_VEC_CAST(th) = DD_AVX_VEC_CAST(t0); \
	DD_AVX_VEC_CAST(bl) = _mm_add_sd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(th) = _mm_add_sd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(bl)); \
	DD_AVX_VEC_CAST(t0) = _mm_sub_sd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(t0)); \
	DD_AVX_VEC_CAST(bl) = _mm_sub_sd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(t0)); \
	DD_AVX_VEC_CAST(bl) = _mm_add_sd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(eh)); \
	DD_AVX_VEC_CAST(sh) = _mm_add_sd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(bl)); \
	_mm_store_sd(&(a_hi),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(sh) = _mm_sub_sd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(bl) = _mm_sub_sd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(sh)); \
	_mm_store_sd(&(a_lo),DD_AVX_VEC_CAST(bl))

#define DD_AVX_ADD2_SSE2_CORE \
	DD_AVX_VEC_CAST(sh) = _mm_add_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(th) = _mm_sub_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(t0) = _mm_sub_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(ch) = _mm_sub_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(bh) = _mm_sub_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(t0)); \
	DD_AVX_VEC_CAST(bh) = _mm_add_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(sl) = _mm_add_pd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(p2)); \
	DD_AVX_VEC_CAST(th) = _mm_sub_pd(DD_AVX_VEC_CAST(sl),DD_AVX_VEC_CAST(bl)); \
	DD_AVX_VEC_CAST(t0) = _mm_sub_pd(DD_AVX_VEC_CAST(sl),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(p2) = _mm_sub_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(bl) = _mm_sub_pd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(t0)); \
	DD_AVX_VEC_CAST(bl) = _mm_add_pd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(p2)); \
	DD_AVX_VEC_CAST(bh) = _mm_add_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(sl)); \
	DD_AVX_VEC_CAST(th) = DD_AVX_VEC_CAST(sh); \
	DD_AVX_VEC_CAST(th) = _mm_add_pd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(sh) = _mm_sub_pd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(bh) = _mm_sub_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(bh) = _mm_add_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(bl)); \
	DD_AVX_VEC_CAST(sh) = _mm_add_pd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(bh))
