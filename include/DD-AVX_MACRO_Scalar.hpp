/* Copyright (C) T.Hishinuma, All rights reserved.*/
#ifndef DD_AVX_MACRO_SCALAR_H_
#define DD_AVX_MACRO_SCALAR_H_

#define SPLITTER 134217729.0

//#define DD_AVX_DECLAR\
//   double p1,p2,tq,bhi,blo,chi,clo,sh,eh,sl,el,th,tl

/**********************************************************
 *                                                        *
 *                      Scalar                            *
 *                                                        *
 **********************************************************/
#define DD_AVX_MINUS(a_hi,a_lo)   \
	(a_hi) = -(a_hi); \
	(a_lo) = -(a_lo)

#define DD_AVX_ZERO(a_hi,a_lo)   \
	(a_hi) = 0.0; \
	(a_lo) = 0.0

#define DD_AVX_ONE(a_hi,a_lo)   \
	(a_hi) = 1.0; \
	(a_lo) = 0.0

#define DD_AVX_FAST_TWO_SUM(a,b,r,e)   \
	(r) = (a) + (b); \
	(e) = (b)  - ((r) - (a))

#define DD_AVX_TWO_SUM(a,b,r,e)   \
	(r) =  (a) + (b); \
	th  =  (r) - (a); \
	(e) =  ((a) - ((r) - th)) + ((b) - th)

#define DD_AVX_TWO_DIFF(a,b,r,e)   \
	(r) =  (a) - (b); \
	th  =  (r) - (a); \
	(e) =  ((a) - ((r) - th)) - ((b) + th)

#define DD_AVX_SPLIT(b,b_hi,b_lo) \
	tq     = SPLITTER * (b); \
	(b_hi) = tq - (tq-(b));  \
	(b_lo) = (b) - (b_hi);   \
/*********************************************************/
#ifndef HAS_FMA
	#define DD_AVX_TWO_PROD(a,b,r,e)   \
		(r)  = (a) * (b); \
		DD_AVX_SPLIT((a),bhi,blo); \
		DD_AVX_SPLIT((b),chi,clo); \
		(e)  = ((bhi*chi-(r))+bhi*clo+blo*chi)+blo*clo
#else
	#define DD_AVX_TWO_PROD(a,b,r,e)   \
		(r)  = (-(a)) * (b); \
		(e)  = (a) * (b) + (r)
#endif
/*********************************************************/

/*********************************************************/
#ifndef HAS_FMA
	#define DD_AVX_TWO_SQR(a,r,e)   \
		(r)  = (a) * (a); \
		DD_AVX_SPLIT((a),bhi,blo); \
		(e)  = ((bhi*bhi-(r))+2.0*bhi*blo)+blo*blo
#else
	#define DD_AVX_TWO_SQR(a,r,e)   \
		(r)  = (-(a)) * (a); \
		(e)  = (a) * (a) + (r)
#endif
/*********************************************************/
#define DD_AVX_ADD(a_hi,a_lo,b_hi,b_lo,c_hi,c_lo) \
	DD_AVX_TWO_SUM((b_hi),(c_hi),sh,eh); \
	eh += (b_lo); \
	eh += (c_lo); \
	DD_AVX_FAST_TWO_SUM(sh,eh,(a_hi),(a_lo))
/*********************************************************/
#define DD_AVX_MUL(a_hi,a_lo,b_hi,b_lo,c_hi,c_lo) \
	DD_AVX_TWO_PROD((b_hi),(c_hi),p1,p2); \
	p2 += ((b_hi) * (c_lo)); \
	p2 += ((b_lo) * (c_hi)); \
	DD_AVX_FAST_TWO_SUM(p1,p2,(a_hi),(a_lo))

#define DD_AVX_MULD(a_hi,a_lo,b_hi,b_lo,c) \
	DD_AVX_TWO_PROD((b_hi),(c),p1,p2); \
	p2 += ((b_lo) * (c)); \
	DD_AVX_FAST_TWO_SUM(p1,p2,(a_hi),(a_lo))

#define DD_AVX_SQR(a_hi,a_lo,b_hi,b_lo) \
	DD_AVX_TWO_SQR((b_hi),p1,p2); \
	p2 += (2.0*(b_hi) * (b_lo)); \
	p2 += ((b_lo) * (b_lo)); \
	DD_AVX_FAST_TWO_SUM(p1,p2,(a_hi),(a_lo))

/*********************************************************/
#define DD_AVX_DIV(a_hi,a_lo,b_hi,b_lo,c_hi,c_lo) \
	tl  = (b_hi) / (c_hi); \
	DD_AVX_MULD(eh,el,(c_hi),(c_lo),tl); \
	DD_AVX_TWO_DIFF((b_hi),eh,sh,sl); \
	sl -= el; \
	sl += (b_lo); \
	th  = (sh+sl) / (c_hi); \
	DD_AVX_FAST_TWO_SUM(tl,th,(a_hi),(a_lo))
 /**********************************************************
  (a_hi,a_lo) <- SQRT( (b_hi,b_lo) )
 **********************************************************/
#define DD_AVX_SQRT(a_hi,a_lo,b_hi,b_lo) \
	if( (b_hi)==0 ) \
	{ \
		(a_hi) = (a_lo) = 0.0; \
	   	printf("sqrt error a is zero"); \
		abort(); \
	} \
	if( (b_hi)<0 ) \
	{ \
		printf("ERROR bh=%e\n",(b_hi)); \
		(a_hi) = (a_lo) = 0.0; \
		abort(); \
	} \
	p1  = 1.0 / sqrt((b_hi)); \
	p2 = (b_hi) * p1; \
	p1  = p1 * 0.5; \
	DD_AVX_TWO_SQR(p2,chi,clo); \
	DD_AVX_ADD(th,eh,(b_hi),(b_lo),-chi,-clo); \
	p1  = p1 * th; \
	DD_AVX_FAST_TWO_SUM(p1,p2,(a_hi),(a_lo))
/*********************************************************
  (d_hi,d_lo) <- (a_hi,a_lo) + (b_hi,b_lo) * (c_hi,c_lo)
 **********************************************************/
#define DD_AVX_FMA(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo,c_hi,c_lo) \
	DD_AVX_MUL(chi,p2,(b_hi),(b_lo),(c_hi),(c_lo)); \
	DD_AVX_ADD((d_hi),(d_lo),(a_hi),(a_lo),chi,p2)
/**********************************************************
 * DD_AVX_FMAD(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo,c)         *
 **********************************************************
  (d_hi,d_lo) <- (a_hi,a_lo) + (b_hi,b_lo) * c
 **********************************************************/
#define DD_AVX_FMAD(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo,c) \
	DD_AVX_MULD(chi,p2,(b_hi),(b_lo),(c)); \
	DD_AVX_ADD((d_hi),(d_lo),(a_hi),(a_lo),chi,p2)
/**********************************************************
 * DD_AVX_FSA(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo)            *
 **********************************************************
  (d_hi,d_lo) <- (a_hi,a_lo) + (b_hi,b_lo) * (b_hi,b_lo)
 **********************************************************/
#define DD_AVX_FSA(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo) \
	DD_AVX_SQR(bhi,p2,(b_hi),(b_lo)); \
	DD_AVX_ADD((d_hi),(d_lo),(a_hi),(a_lo),bhi,p2)

#endif
