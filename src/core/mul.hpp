#pragma once
#ifndef DD_AVX_CORE_MUL_HPP_
#define DD_AVX_CORE_MUL_HPP_

namespace ddavx_core {

inline void Mul(reg &a_hi, reg &a_lo, const reg &b_hi, const reg &b_lo,
                const reg &c_hi, const reg &c_lo, registers c) {
  c.bh = b_hi;
  c.bl = b_lo;
  c.ch = c_hi;
  c.cl = c_lo;

#if defined USE_FMA
  c.p1 = mul(c.minus, c.bh);
  c.p1 = mul(c.p1, c.ch);
  c.p2 = fmadd(c.bh, c.ch, c.p1);
  c.p1 = mul(c.minus, c.p1);
  c.p2 = fmadd(c.bh, c.cl, c.p2);
  c.p2 = fmadd(c.bl, c.ch, c.p2);
  c.ch = add(c.p1, c.p2);
#else
  c.p1 = mul(c.bh, c.ch);
  c.sh = mul(c.sp, c.bh);
  c.sl = mul(c.sp, c.ch);
  c.th = sub(c.sh, c.bh);
  c.tl = sub(c.sl, c.ch);
  c.sh = sub(c.sh, c.th);
  c.sl = sub(c.sl, c.tl);
  c.t1 = mul(c.bh, c.cl);
  c.wh = sub(c.bh, c.sh);
  c.t2 = mul(c.ch, c.bl);
  c.wl = sub(c.ch, c.sl);
  c.t0 = mul(c.wh, c.wl);
  c.p2 = mul(c.sh, c.sl);
  c.sh = mul(c.sh, c.wl);
  c.sl = mul(c.sl, c.wh);
  c.p2 = sub(c.p2, c.p1);
  c.p2 = add(c.p2, c.sh);
  c.p2 = add(c.p2, c.sl);
  c.p2 = add(c.p2, c.t0);
  c.p2 = add(c.p2, c.t1);
  c.p2 = add(c.p2, c.t2);
  c.ch = add(c.p1, c.p2);
#endif
  a_hi = c.ch;
  c.ch = sub(c.ch, c.p1);
  c.p2 = sub(c.p2, c.ch);
  a_lo = c.p2;
}

inline void Mul(reg &a_hi, const reg &b_hi, const reg &b_lo, const reg &c_hi,
                const reg &c_lo, registers c) {
  c.bh = b_hi;
  c.bl = b_lo;
  c.ch = c_hi;
  c.cl = c_lo;

#if defined USE_FMA
  c.p1 = mul(c.minus, c.bh);
  c.p1 = mul(c.p1, c.ch);
  c.p2 = fmadd(c.bh, c.ch, c.p1);
  c.p1 = mul(c.minus, c.p1);
  c.p2 = fmadd(c.bh, c.cl, c.p2);
  c.p2 = fmadd(c.bl, c.ch, c.p2);
  c.ch = add(c.p1, c.p2);
#else
  c.p1 = mul(c.bh, c.ch);
  c.sh = mul(c.sp, c.bh);
  c.sl = mul(c.sp, c.ch);
  c.th = sub(c.sh, c.bh);
  c.tl = sub(c.sl, c.ch);
  c.sh = sub(c.sh, c.th);
  c.sl = sub(c.sl, c.tl);
  c.t1 = mul(c.bh, c.cl);
  c.wh = sub(c.bh, c.sh);
  c.t2 = mul(c.ch, c.bl);
  c.wl = sub(c.ch, c.sl);
  c.t0 = mul(c.wh, c.wl);
  c.p2 = mul(c.sh, c.sl);
  c.sh = mul(c.sh, c.wl);
  c.sl = mul(c.sl, c.wh);
  c.p2 = sub(c.p2, c.p1);
  c.p2 = add(c.p2, c.sh);
  c.p2 = add(c.p2, c.sl);
  c.p2 = add(c.p2, c.t0);
  c.p2 = add(c.p2, c.t1);
  c.p2 = add(c.p2, c.t2);
  c.ch = add(c.p1, c.p2);
#endif
  a_hi = c.ch;
}

inline void Muld(reg &a_hi, reg &a_lo, const reg &b_hi, const reg &b_lo,
                 const reg &c_hi, registers c) {

  c.bh = b_hi;
  c.bl = b_lo;
  c.ch = c_hi;

#if defined USE_FMA
  c.p1 = mul(c.minus, c.bh);
  c.p1 = mul(c.p1, c.ch);
  c.p2 = fmadd(c.bh, c.ch, c.p1);
  c.p1 = mul(c.minus, c.p1);
  c.p2 = fmadd(c.bl, c.ch, c.p2);
  c.ch = add(c.p1, c.p2);
#else
  c.p1 = mul(c.bh, c.ch);
  c.bl = mul(c.bl, c.ch);
  c.sh = mul(c.sp, c.bh);
  c.th = sub(c.sh, c.bh);
  c.sh = sub(c.sh, c.th);
  c.bh = sub(c.bh, c.sh);
  c.sl = mul(c.sp, c.ch);
  c.tl = sub(c.sl, c.ch);
  c.sl = sub(c.sl, c.tl);
  c.ch = sub(c.ch, c.sl);
  c.t2 = mul(c.bh, c.ch);
  c.p2 = mul(c.sh, c.sl);
  c.t0 = mul(c.sh, c.ch);
  c.t1 = mul(c.sl, c.bh);
  c.p2 = sub(c.p2, c.p1);
  c.p2 = add(c.p2, c.t0);
  c.p2 = add(c.p2, c.t1);
  c.p2 = add(c.p2, c.t2);
  c.p2 = add(c.p2, c.bl);
  c.ch = add(c.p1, c.p2);
#endif
  a_hi = c.ch;
  c.ch = sub(c.ch, c.p1);
  c.p2 = sub(c.p2, c.ch);
  a_lo = c.p2;
}

inline void Mul(double &a_hi, double &a_lo, const double &b_hi,
                const double &b_lo, const double &c_hi, const double &c_lo) {
  dd_real a, b, c;
  a.x[0] = a_hi;
  a.x[1] = a_lo;
  b.x[0] = b_hi;
  b.x[1] = b_lo;
  c.x[0] = c_hi;
  c.x[1] = c_lo;
  a = b * c;

  a_hi = a.x[0], a_lo = a.x[1];
}

inline void Mul(double &a_hi, const double &b_hi, const double &b_lo,
                const double &c_hi, const double &c_lo) {
  dd_real a, b, c;
  a.x[0] = a_hi;
  a.x[1] = 0.0;
  b.x[0] = b_hi;
  b.x[1] = b_lo;
  c.x[0] = c_hi;
  c.x[1] = c_lo;
  a = b * c;

  a_hi = a.x[0];
}

inline void Muld(double &a_hi, double &a_lo, const double &b_hi,
                 const double &b_lo, const double &c_hi) {
  dd_real a, b, c;
  a.x[0] = a_hi;
  a.x[1] = a_lo;
  b.x[0] = b_hi;
  b.x[1] = b_lo;
  c.x[0] = c_hi;
  c.x[1] = 0.0;
  a = b * c;

  a_hi = a.x[0];
}

} // namespace ddavx_core
#endif
