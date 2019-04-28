/* Copyright (C) T.Hishinuma, All rights reserved.*/
#ifndef DD_AVX_MACRO_SSE2_H_
#define DD_AVX_MACRO_SSE2_H_

#include <emmintrin.h>
#define SPLITTER 134217729.0

#define DD_AVX_VEC_CAST(VAR) (VAR)

#define DD_AVX_DECLAR\
   __m128d bh,ch,sh,wh,th,bl,cl,sl,wl,tl,p1,p2,t0,t1,t2,t3,eh


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


/**********************************************************
 *                                                        *
 *                      SSE2(PD)                          *
 *                                                        *
 **********************************************************/
/**********************************************************
 * DD_AVX_MUL2_SSE2_LOAD(b_hi,b_lo,c_hi,c_lo)           *
 **********************************************************
  (b_hi,b_lo)  (c_hi,c_lo)
 **********************************************************/
#define DD_AVX_MUL2_SSE2_LOAD(b_hi,b_lo,c_hi,c_lo) \
	DD_AVX_VEC_CAST(t0)  = _mm_set_pd(SPLITTER,SPLITTER); \
	DD_AVX_VEC_CAST(bh) = _mm_loadu_pd(&(b_hi)); \
	DD_AVX_VEC_CAST(ch) = _mm_loadu_pd(&(c_hi)); \
	DD_AVX_VEC_CAST(bl) = _mm_loadu_pd(&(b_lo)); \
	DD_AVX_VEC_CAST(cl) = _mm_loadu_pd(&(c_lo))
/**********************************************************
 * DD_AVX_MULD2_SSE2_LOAD(b_hi,b_lo,c)                  *
 **********************************************************
  (b_hi,b_lo)  (c)
 **********************************************************/
#define DD_AVX_MULD2_SSE2_LOAD(b_hi,b_lo,c) \
	DD_AVX_VEC_CAST(t0)  = _mm_set_pd(SPLITTER,SPLITTER); \
	DD_AVX_VEC_CAST(bh)  = _mm_loadu_pd(&(b_hi)); \
	DD_AVX_VEC_CAST(bl)  = _mm_loadu_pd(&(b_lo)); \
	DD_AVX_VEC_CAST(ch)  = _mm_loadu_pd(&(c))
#define DD_AVX_MULD2_SSE2_LOAD_SD(b0_hi,b0_lo,b1_hi,b1_lo,c) \
	DD_AVX_VEC_CAST(t0)  = _mm_set_pd(SPLITTER,SPLITTER); \
	DD_AVX_VEC_CAST(bh)  = _mm_set_pd((b1_hi),(b0_hi)); \
	DD_AVX_VEC_CAST(bl)  = _mm_set_pd((b1_lo),(b0_lo)); \
	DD_AVX_VEC_CAST(ch)  = _mm_loadu_pd(&(c))
/**********************************************************
 * DD_AVX_SQR2_SSE2_LOAD(b_hi,b_lo)                     *
 **********************************************************
  (b_hi,b_lo)
 **********************************************************/
#define DD_AVX_SQR2_SSE2_LOAD(b_hi,b_lo) \
	DD_AVX_VEC_CAST(ch)  = _mm_set_pd(SPLITTER,SPLITTER); \
	DD_AVX_VEC_CAST(bh) = _mm_loadu_pd(&(b_hi)); \
	DD_AVX_VEC_CAST(bl) = _mm_loadu_pd(&(b_lo))
/**********************************************************
 * DD_AVX_MUL2_SSE2_STORE(a_hi,a_lo)                    *
 **********************************************************
  (a_hi,a_lo) <-
 **********************************************************/
#define DD_AVX_MUL2_SSE2_STORE(a_hi,a_lo) \
	_mm_storeu_pd(&(a_hi),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(ch)  = _mm_sub_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(p1)); \
	DD_AVX_VEC_CAST(p2)  = _mm_sub_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(ch)); \
	_mm_storeu_pd(&(a_lo),DD_AVX_VEC_CAST(p2))
#define DD_AVX_MUL2_SSE2_STOREU(a_hi,a_lo) \
	_mm_storeu_pd(&(a_hi),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(ch)  = _mm_sub_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(p1)); \
	DD_AVX_VEC_CAST(p2)  = _mm_sub_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(ch)); \
	_mm_storeu_pd(&(a_lo),DD_AVX_VEC_CAST(p2))
/**********************************************************
 * DD_AVX_ADD2_SSE2_LOAD(b_hi,b_lo,c_hi,c_lo)           *
 **********************************************************
  (b_hi,b_lo)  (c_hi,c_lo)
 **********************************************************/
#ifndef USE_FAST_QUAD_ADD
#define DD_AVX_ADD2_SSE2_LOAD(b_hi,b_lo,c_hi,c_lo) \
	DD_AVX_VEC_CAST(sh) = _mm_set_pd((b_lo),(b_hi)); \
	DD_AVX_VEC_CAST(bl) = _mm_set_pd((c_lo),(c_hi))
#else
#define DD_AVX_ADD2_SSE2_LOAD(b_hi,b_lo,c_hi,c_lo) \
	DD_AVX_VEC_CAST(eh) = _mm_set_sd((b_hi)); \
	DD_AVX_VEC_CAST(cl) = _mm_set_sd((b_lo)); \
	DD_AVX_VEC_CAST(sh) = _mm_set_sd((c_hi)); \
	DD_AVX_VEC_CAST(wh) = _mm_set_sd((c_lo))
#endif
/**********************************************************
 * DD_AVX_ADD2_SSE2_STORE(a_hi,a_lo)                    *
 **********************************************************
  (a_hi,a_lo) <-
 **********************************************************/
#define DD_AVX_ADD2_SSE2_STORE(a_hi,a_lo) \
	_mm_storeu_pd(&(a_hi),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(sh) = _mm_sub_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(bh) = _mm_sub_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(sh)); \
	_mm_storeu_pd(&(a_lo),DD_AVX_VEC_CAST(bh))
#define DD_AVX_ADD2_SSE2_STORE_SD(a0_hi,a0_lo,a1_hi,a1_lo) \
	_mm_storel_pd(&(a0_hi),DD_AVX_VEC_CAST(sh)); \
	_mm_storeh_pd(&(a1_hi),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(sh) = _mm_sub_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(bh) = _mm_sub_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(sh)); \
	_mm_storel_pd(&(a0_lo),DD_AVX_VEC_CAST(bh)); \
	_mm_storeh_pd(&(a1_lo),DD_AVX_VEC_CAST(bh))
/**********************************************************
 * DD_AVX_FMA2_SSE2_LOAD(a_hi,a_lo)                     *
 **********************************************************
  (a_hi,a_lo)
 **********************************************************/
#define DD_AVX_FMA2_SSE2_LOAD(a_hi,a_lo) \
	DD_AVX_VEC_CAST(t1)  = _mm_sub_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(p1)); \
	DD_AVX_VEC_CAST(p2)  = _mm_sub_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(t1)); \
	DD_AVX_VEC_CAST(bh) = _mm_loadu_pd(&(a_hi)); \
	DD_AVX_VEC_CAST(bl) = _mm_loadu_pd(&(a_lo))
#define DD_AVX_FMA2_SSE2_LOAD_SD(a0_hi,a0_lo,a1_hi,a1_lo) \
	DD_AVX_VEC_CAST(t1)  = _mm_sub_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(p1)); \
	DD_AVX_VEC_CAST(p2)  = _mm_sub_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(t1)); \
	DD_AVX_VEC_CAST(bh)  = _mm_set_pd((a1_hi),(a0_hi)); \
	DD_AVX_VEC_CAST(bl)  = _mm_set_pd((a1_lo),(a0_lo))
/*********************************************************
 * DD_AVX_MUL2_SSE2_CORE                                *
 **********************************************************
  (b_hi,b_lo) x (c_hi,c_lo)
 **********************************************************/
#define DD_AVX_MUL2_SSE2_CORE \
	DD_AVX_VEC_CAST(p1)  = _mm_mul_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(sh)  = _mm_mul_pd(DD_AVX_VEC_CAST(t0),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(sl)  = _mm_mul_pd(DD_AVX_VEC_CAST(t0),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(th)  = _mm_sub_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(tl)  = _mm_sub_pd(DD_AVX_VEC_CAST(sl),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(sh)  = _mm_sub_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(sl)  = _mm_sub_pd(DD_AVX_VEC_CAST(sl),DD_AVX_VEC_CAST(tl)); \
	DD_AVX_VEC_CAST(t1)  = _mm_mul_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(cl)); \
	DD_AVX_VEC_CAST(wh)  = _mm_sub_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(t2)  = _mm_mul_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(bl)); \
	DD_AVX_VEC_CAST(wl)  = _mm_sub_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(sl)); \
	DD_AVX_VEC_CAST(t0)  = _mm_mul_pd(DD_AVX_VEC_CAST(wh),DD_AVX_VEC_CAST(wl)); \
	DD_AVX_VEC_CAST(p2)  = _mm_mul_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(sl)); \
	DD_AVX_VEC_CAST(sh)  = _mm_mul_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(wl)); \
	DD_AVX_VEC_CAST(sl)  = _mm_mul_pd(DD_AVX_VEC_CAST(sl),DD_AVX_VEC_CAST(wh)); \
	DD_AVX_VEC_CAST(p2)  = _mm_sub_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(p1)); \
	DD_AVX_VEC_CAST(p2)  = _mm_add_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(p2)  = _mm_add_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(sl)); \
	DD_AVX_VEC_CAST(p2)  = _mm_add_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(t0)); \
	DD_AVX_VEC_CAST(p2)  = _mm_add_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(t1)); \
	DD_AVX_VEC_CAST(p2)  = _mm_add_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(t2)); \
	DD_AVX_VEC_CAST(ch)  = _mm_add_pd(DD_AVX_VEC_CAST(p1),DD_AVX_VEC_CAST(p2))
/**********************************************************
 * DD_AVX_MULD2_SSE2_CORE                               *
 **********************************************************
  (b_hi,b_lo) x c
 **********************************************************/
#define DD_AVX_MULD2_SSE2_CORE \
	DD_AVX_VEC_CAST(p1)  = _mm_mul_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(bl)  = _mm_mul_pd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(sh)  = _mm_mul_pd(DD_AVX_VEC_CAST(t0),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(th)  = _mm_sub_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(sh)  = _mm_sub_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(th)); \
	DD_AVX_VEC_CAST(bh)  = _mm_sub_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(sh)); \
	DD_AVX_VEC_CAST(sl)  = _mm_mul_pd(DD_AVX_VEC_CAST(t0),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(tl)  = _mm_sub_pd(DD_AVX_VEC_CAST(sl),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(sl)  = _mm_sub_pd(DD_AVX_VEC_CAST(sl),DD_AVX_VEC_CAST(tl)); \
	DD_AVX_VEC_CAST(ch)  = _mm_sub_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(sl)); \
	DD_AVX_VEC_CAST(t2)  = _mm_mul_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(p2)  = _mm_mul_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(sl)); \
	DD_AVX_VEC_CAST(t0)  = _mm_mul_pd(DD_AVX_VEC_CAST(sh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(t1)  = _mm_mul_pd(DD_AVX_VEC_CAST(sl),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(p2)  = _mm_sub_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(p1)); \
	DD_AVX_VEC_CAST(p2)  = _mm_add_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(t0)); \
	DD_AVX_VEC_CAST(p2)  = _mm_add_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(t1)); \
	DD_AVX_VEC_CAST(p2)  = _mm_add_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(t2)); \
	DD_AVX_VEC_CAST(p2)  = _mm_add_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(bl)); \
	DD_AVX_VEC_CAST(ch)  = _mm_add_pd(DD_AVX_VEC_CAST(p1),DD_AVX_VEC_CAST(p2))
/**********************************************************
 * DD_AVX_SQR2_SSE2_CORE                                *
 **********************************************************
  (b_hi,b_lo) x (b_hi,b_lo)
 **********************************************************/
#define DD_AVX_SQR2_SSE2_CORE \
	DD_AVX_VEC_CAST(p1)  = _mm_mul_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(ch)  = _mm_mul_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(p2)  = _mm_sub_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(ch)  = _mm_sub_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(p2)); \
	DD_AVX_VEC_CAST(cl)  = _mm_sub_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(p2)  = _mm_mul_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(ch)  = _mm_add_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(ch)  = _mm_mul_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(cl)); \
	DD_AVX_VEC_CAST(cl)  = _mm_mul_pd(DD_AVX_VEC_CAST(cl),DD_AVX_VEC_CAST(cl)); \
	DD_AVX_VEC_CAST(p2)  = _mm_sub_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(p1)); \
	DD_AVX_VEC_CAST(p2)  = _mm_add_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(ch)); \
	DD_AVX_VEC_CAST(p2)  = _mm_add_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(cl)); \
	DD_AVX_VEC_CAST(bh)  = _mm_add_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(bh)  = _mm_mul_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(bl)); \
	DD_AVX_VEC_CAST(bl)  = _mm_mul_pd(DD_AVX_VEC_CAST(bl),DD_AVX_VEC_CAST(bl)); \
	DD_AVX_VEC_CAST(p2)  = _mm_add_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(bh)); \
	DD_AVX_VEC_CAST(p2)  = _mm_add_pd(DD_AVX_VEC_CAST(p2),DD_AVX_VEC_CAST(bl)); \
	DD_AVX_VEC_CAST(ch)  = _mm_add_pd(DD_AVX_VEC_CAST(p1),DD_AVX_VEC_CAST(p2))
/**********************************************************
 * DD_AVX_ADD2_SSE2_CORE                                *
 **********************************************************
  (b_hi,b_lo) + (c_hi,c_lo)
 **********************************************************/
#ifndef USE_FAST_QUAD_ADD
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
#else
	#define DD_AVX_ADD2_SSE2_CORE \
		DD_AVX_VEC_CAST(th) = _mm_add_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(ch)); \
		DD_AVX_VEC_CAST(wh) = _mm_sub_pd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(bh)); \
		DD_AVX_VEC_CAST(t0) = _mm_sub_pd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(wh)); \
		DD_AVX_VEC_CAST(ch) = _mm_sub_pd(DD_AVX_VEC_CAST(ch),DD_AVX_VEC_CAST(wh)); \
		DD_AVX_VEC_CAST(bh) = _mm_sub_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(t0)); \
		DD_AVX_VEC_CAST(bh) = _mm_add_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(ch)); \
		DD_AVX_VEC_CAST(bh) = _mm_add_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(bl)); \
		DD_AVX_VEC_CAST(bh) = _mm_add_pd(DD_AVX_VEC_CAST(bh),DD_AVX_VEC_CAST(p2)); \
		DD_AVX_VEC_CAST(sh) = _mm_add_pd(DD_AVX_VEC_CAST(th),DD_AVX_VEC_CAST(bh))
#endif
/**********************************************************
 * DD_AVX_MUL2_SSE2(a_hi,a_lo,b_hi,b_lo,c_hi,c_lo)      *
 **********************************************************
  (a_hi,a_lo) <- (b_hi,b_lo) x (c_hi,c_lo)
 **********************************************************/
#define DD_AVX_MUL2_SSE2(a_hi,a_lo,b_hi,b_lo,c_hi,c_lo) \
	DD_AVX_MUL2_SSE2_LOAD((b_hi),(b_lo),(c_hi),(c_lo)); \
	DD_AVX_MUL2_SSE2_CORE; \
	DD_AVX_MUL2_SSE2_STORE((a_hi),(a_lo))
/**********************************************************
 * DD_AVX_MULD2_SSE2(a_hi,a_lo,b_hi,b_lo,c)             *
 **********************************************************
  (a_hi,a_lo) <- (b_hi,b_lo) x c
 **********************************************************/
#define DD_AVX_MULD2_SSE2(a_hi,a_lo,b_hi,b_lo,c) \
	DD_AVX_MULD2_SSE2_LOAD((b_hi),(b_lo),(c)); \
	DD_AVX_MULD2_SSE2_CORE; \
	DD_AVX_MUL2_SSE2_STORE((a_hi),(a_lo))
/**********************************************************
 * DD_AVX_SQR2_SSE2(a_hi,a_lo,b_hi,b_lo)                *
 **********************************************************
  (a_hi,a_lo) <- (b_hi,b_lo) x (b_hi,b_lo)
 **********************************************************/
#define DD_AVX_SQR2_SSE2(a_hi,a_lo,b_hi,b_lo) \
	DD_AVX_SQR2_SSE2_LOAD((b_hi),(b_lo)); \
	DD_AVX_SQR2_SSE2_CORE; \
	DD_AVX_MUL2_SSE2_STORE((a_hi),(a_lo))
/**********************************************************
 * DD_AVX_ADD2_SSE2(a_hi,a_lo,b_hi,b_lo,c_hi,c_lo)      *
 **********************************************************
  (a_hi,a_lo) <- (b_hi,b_lo) + (c_hi,c_lo)
 **********************************************************/
#define DD_AVX_ADD2_SSE2(a_hi,a_lo,b_hi,b_lo,c_hi,c_lo) \
	DD_AVX_ADD2_SSE2_LOAD((b_hi),(b_lo),(c_hi),(c_lo)); \
	DD_AVX_ADD2_SSE2_CORE; \
	DD_AVX_ADD2_SSE2_STORE((a_hi),(a_lo))
/***************************************************************
 * DD_AVX_FMA2_SSE2(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo,c_hi,c_lo) *
 ***************************************************************
  (d_hi,d_lo) <- (a_hi,a_lo) + (b_hi,b_lo) * (c_hi,c_lo)
 ***************************************************************/
#define DD_AVX_FMA2_SSE2(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo,c_hi,c_lo) \
	DD_AVX_MUL2_SSE2_LOAD((b_hi),(b_lo),(c_hi),(c_lo)); \
	DD_AVX_MUL2_SSE2_CORE; \
	DD_AVX_FMA2_SSE2_LOAD((a_hi),(a_lo)); \
	DD_AVX_ADD2_SSE2_CORE; \
	DD_AVX_ADD2_SSE2_STORE((d_hi),(d_lo))
/***************************************************************************
 * DD_AVX_FMAD2_SSE2(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo,c)                    *
 * DD_AVX_FMAD2_SSE2_LDSD(d_hi,d_lo,a_hi,a_lo,b0_hi,b0_lo,b1_hi,b1_lo,c) *
 ***************************************************************************
  (d_hi,d_lo) <- (a_hi,a_lo) + (b_hi,b_lo) * c
 ***************************************************************/
#define DD_AVX_FMAD2_SSE2(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo,c) \
	DD_AVX_MULD2_SSE2_LOAD((b_hi),(b_lo),(c)); \
	DD_AVX_MULD2_SSE2_CORE; \
	DD_AVX_FMA2_SSE2_LOAD((a_hi),(a_lo)); \
	DD_AVX_ADD2_SSE2_CORE; \
	DD_AVX_ADD2_SSE2_STORE((d_hi),(d_lo))
/****************************************************************/
#define DD_AVX_FMAD2_SSE2_LDSD(d_hi,d_lo,a_hi,a_lo,b0_hi,b0_lo,b1_hi,b1_lo,c) \
	DD_AVX_MULD2_SSE2_LOAD_SD((b0_hi),(b0_lo),(b1_hi),(b1_lo),(c)); \
	DD_AVX_MULD2_SSE2_CORE; \
	DD_AVX_FMA2_SSE2_LOAD((a_hi),(a_lo)); \
	DD_AVX_ADD2_SSE2_CORE; \
	DD_AVX_ADD2_SSE2_STORE((d_hi),(d_lo))
/****************************************************************/
#define DD_AVX_FMAD2_SSE2_STSD(d0_hi,d0_lo,d1_hi,d1_lo,a0_hi,a0_lo,a1_hi,a1_lo,b0_hi,b0_lo,b1_hi,b1_lo,c) \
	DD_AVX_MULD2_SSE2_LOAD_SD((b0_hi),(b0_lo),(b1_hi),(b1_lo),(c)); \
	DD_AVX_MULD2_SSE2_CORE; \
	DD_AVX_FMA2_SSE2_LOAD_SD((a0_hi),(a0_lo),(a1_hi),(a1_lo)); \
	DD_AVX_ADD2_SSE2_CORE; \
	DD_AVX_ADD2_SSE2_STORE_SD((d0_hi),(d0_lo),(d1_hi),(d1_lo))
/***************************************************************
 * DD_AVX_FSA2_SSE2(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo)           *
 ***************************************************************
  (d_hi,d_lo) <- (a_hi,a_lo) + (b_hi,b_lo) * (b_hi,b_lo)
 ***************************************************************/
#define DD_AVX_FSA2_SSE2(d_hi,d_lo,a_hi,a_lo,b_hi,b_lo) \
	DD_AVX_SQR2_SSE2_LOAD((b_hi),(b_lo)); \
	DD_AVX_SQR2_SSE2_CORE; \
	DD_AVX_FMA2_SSE2_LOAD((a_hi),(a_lo)); \
	DD_AVX_ADD2_SSE2_CORE; \
	DD_AVX_ADD2_SSE2_STORE((d_hi),(d_lo))

#endif
