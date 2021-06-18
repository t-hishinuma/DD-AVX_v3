#pragma once
#ifndef DD_AVX_CORE_ADD_HPP_
#define DD_AVX_CORE_ADD_HPP_

namespace ddavx_core {
inline void Add(reg &a_hi, reg &a_lo, const reg &b_hi, const reg &b_lo,
                const reg &c_hi, const reg &c_lo, registers &c) {
  c.bh = b_hi;
  c.bl = b_lo;
  c.ch = c_hi;
  c.p2 = c_lo;

  c.sh = add(c.bh, c.ch);
  c.th = sub(c.sh, c.bh);
  c.t0 = sub(c.sh, c.th);
  c.ch = sub(c.ch, c.th);
  c.bh = sub(c.bh, c.t0);
  c.bh = add(c.bh, c.ch);
  c.sl = add(c.bl, c.p2);
  c.th = sub(c.sl, c.bl);
  c.t0 = sub(c.sl, c.th);
  c.p2 = sub(c.p2, c.th);
  c.bl = sub(c.bl, c.t0);
  c.bl = add(c.bl, c.p2);
  c.bh = add(c.bh, c.sl);
  c.th = c.sh;
  c.th = add(c.th, c.bh);
  c.sh = sub(c.th, c.sh);
  c.bh = sub(c.bh, c.sh);
  c.bh = add(c.bh, c.bl);
  c.sh = add(c.th, c.bh);

  a_hi = c.sh;
  c.sh = sub(c.sh, c.th);
  c.bh = sub(c.bh, c.sh);
  a_lo = c.bh;
}

inline void Add(reg &a_hi, const reg &b_hi, const reg &b_lo, const reg &c_hi,
                const reg &c_lo, registers &c) {
  c.bh = b_hi;
  c.bl = b_lo;
  c.ch = c_hi;
  c.p2 = c_lo;

  c.sh = add(c.bh, c.ch);
  c.th = sub(c.sh, c.bh);
  c.t0 = sub(c.sh, c.th);
  c.ch = sub(c.ch, c.th);
  c.bh = sub(c.bh, c.t0);
  c.bh = add(c.bh, c.ch);
  c.sl = add(c.bl, c.p2);
  c.th = sub(c.sl, c.bl);
  c.t0 = sub(c.sl, c.th);
  c.p2 = sub(c.p2, c.th);
  c.bl = sub(c.bl, c.t0);
  c.bl = add(c.bl, c.p2);
  c.bh = add(c.bh, c.sl);
  c.th = c.sh;
  c.th = add(c.th, c.bh);
  c.sh = sub(c.th, c.sh);
  c.bh = sub(c.bh, c.sh);
  c.bh = add(c.bh, c.bl);
  c.sh = add(c.th, c.bh);

  a_hi = c.sh;
}

inline void Add(double &a_hi, double &a_lo, const double &b_hi,
                const double &b_lo, const double &c_hi, const double &c_lo) {
  dd_real a, b, c;
  a.x[0] = a_hi;
  a.x[1] = a_lo;
  b.x[0] = b_hi;
  b.x[1] = b_lo;
  c.x[0] = c_hi;
  c.x[1] = c_lo;
  a = b + c;

  a_hi = a.x[0], a_lo = a.x[1];
}

inline void Add(double &a_hi, const double &b_hi, const double &b_lo,
                const double &c_hi, const double &c_lo) {
  dd_real a, b, c;
  a.x[0] = a_hi;
  a.x[1] = 0.0;
  b.x[0] = b_hi;
  b.x[1] = b_lo;
  c.x[0] = c_hi;
  c.x[1] = c_lo;
  a = b + c;

  a_hi = a.x[0];
}
} // namespace ddavx_core
#endif
