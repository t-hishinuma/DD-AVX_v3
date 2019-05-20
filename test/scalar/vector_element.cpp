// dd_real(QD) link test
#include<DD-AVX.hpp>
#include<qd/dd_real.h>

int main()
{
	dd_real_vector a(100, 1.2);
	d_real_vector b(100,1.5);

	dd_real alpha = 3;
	double beta = 5;

	//dd vec element = scalar
	a[0] = alpha;
	a[1] = 1.3;

	//dd vec element = dd vector element
	a[0] = alpha;
	a[0] = beta;
	a[0] = a[1];
	a[0] = b[1];

	//dd vec element = d vector element
	a[0] = a[1] + a[0]; // DD[] + DD[]
	a[0] = b[1] + b[0]; // D + D
	a[0] = a[1] + b[0]; // D[] + D

	a[0] = alpha + b[0]; // DD + D
	a[0] = beta + b[0]; // D + D
	a[0] = alpha + beta; // DD + D
	a[0] = alpha + alpha; // DD + DD

 	a[0] = b[0] + beta;
	a[0] = b[0] + alpha;

	a[0] = alpha + b[0];
	a[0] = beta + b[0];

	a[0] = a[0] + alpha;
	a[0] = a[0] + beta;

 	a[0] = alpha + a[0];
 	a[0] = beta + a[0];

	//d vec element = dd vector element
	//b[0] = (double)alpha; //dekinai
	b[0] = beta;
	b[0] = a[1];
	b[0] = b[1];

	//d vec element = d vector element
	//dekinai
 	//b[0] = a[1] + a[0]; // DD[] + DD[]
 	b[0] = double(alpha) + double(alpha); // DD + DD
	beta = double(alpha) + double(alpha); // DD + DD
	beta = alpha + alpha; // DD + DD
	std::cout << beta << alpha << std::endl;
 	b[0] = b[1] + b[0]; // D + D
  	b[0] = a[1] + b[0]; // D[] + D
 	beta = a[1] + b[0]; // D[] + D

	b[0] = alpha + b[0]; // DD + D
	b[0] = beta + b[0]; // D + D
	b[0] = alpha + beta; // DD + D
	b[0] = alpha + alpha; // DD + D

 	b[0] = b[0] + beta;
	b[0] = b[0] + alpha;

	b[0] = alpha + b[0];
	b[0] = beta + b[0];

	b[0] = a[0] + alpha;
	b[0] = a[0] + beta;

 	b[0] = alpha + a[0];
 	b[0] = beta + a[0];

	std::vector<dd_real> xx(10);
	d_real_vector yy(10);
	xx[0] = alpha;
	xx[0] = beta;
	yy[0] = alpha;
	yy[0] = beta;
 	return 0;
}
