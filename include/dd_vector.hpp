#ifndef DD_AVX_VEC_HPP
#define DD_AVX_VEC_HPP

class dd_real_vector{

	private:
		double p1,p2,tq,bhi,blo,chi,clo,sh,eh,sl,el,th,tl,t0,t1,t2,t3;

	public:
		std::vector<double> hi;
		std::vector<double> lo;
		int N;
		double memsize;


		dd_real_vector(){}

		dd_real_vector(int N){
			hi.resize(N);
			lo.resize(N);
		}

		dd_real_vector(int N, double val){
			hi.resize(N, val);
			lo.resize(N, val);
		}

};
#endif
// 		// add
// 		static dd_real add(double a, double b);
// 		dd_real &operator+=(double a);
// 		dd_real &operator+=(const dd_real &a);
//
// 		//minus
// 		static dd_real sub(double a, double b);
// 		dd_real operator-() const;
// 		dd_real &operator-=(double a);
// 		dd_real &operator-=(const dd_real &a);
//
// 		//mul
// 		static dd_real mul(double a, double b);
// 		dd_real &operator*=(double a);
// 		dd_real &operator*=(const dd_real &a);
// 		//div
// 		static dd_real div(double a, double b);
// 		dd_real &operator/=(double a);
// 		dd_real &operator/=(const dd_real &a);
//
// 		dd_real &operator=(double a);
// 		dd_real &operator=(const char *s);
//
// 		at;
// 		operator[];
// 		data;
// 		front;
// 		back;
//
// 		size;
// 		resize;
//
// 	  new
// 	  (allocate)
//
// 	begin
// 	end
//

// QD_API dd_real operator+(const dd_real &a, double b);
// QD_API dd_real operator+(double a, const dd_real &b);
// QD_API dd_real operator+(const dd_real &a, const dd_real &b);
//
// QD_API dd_real operator-(const dd_real &a, double b);
// QD_API dd_real operator-(double a, const dd_real &b);
// QD_API dd_real operator-(const dd_real &a, const dd_real &b);
//
// QD_API dd_real operator*(const dd_real &a, double b);
// QD_API dd_real operator*(double a, const dd_real &b);
// QD_API dd_real operator*(const dd_real &a, const dd_real &b);
//
// QD_API dd_real operator/(const dd_real &a, double b);
// QD_API dd_real operator/(double a, const dd_real &b);
// QD_API dd_real operator/(const dd_real &a, const dd_real &b);
//
// QD_API bool operator==(const dd_real &a, double b);
// QD_API bool operator==(double a, const dd_real &b);
// QD_API bool operator==(const dd_real &a, const dd_real &b);
//
// QD_API bool operator!=(const dd_real &a, double b);
// QD_API bool operator!=(double a, const dd_real &b);
// QD_API bool operator!=(const dd_real &a, const dd_real &b);
//
//       DD_Scalar dot(D_Vector vx, D_Vector vy);
//       DD_Scalar dot(DD_Vector vx, D_Vector vy);
//       DD_Scalar dot(D_Vector vx, DD_Vector vy);
//       DD_Scalar dot(DD_Vector vx, DD_Vector vy);
//
//       DD_Scalar nrm2(D_Vector vx);
//       DD_Scalar nrm2(DD_Vector vx);
//
