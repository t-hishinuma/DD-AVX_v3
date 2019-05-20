#ifndef SCALAR_HPP
#define SCALAR_HPP
#include<DD-AVX.hpp>
class d_real_vector;
class dd_real_vector;
class dd_real_vector_ref;

class dd_real_scalar : public dd_real{
	public:
		dd_real_scalar();
		dd_real_scalar(double hi, double lo);
		dd_real_scalar(double h);
		dd_real_scalar(int h);
		dd_real_scalar(dd_real a);
		dd_real_scalar(dd_real_vector_ref a);

		operator double();
		//operator dd_real();
		operator dd_real_vector_ref();
    	operator std::vector<double>::iterator();

		void operator=(const dd_real a);
		void operator=(const double a);
		void operator=(const dd_real_vector_ref a);
};

#endif
