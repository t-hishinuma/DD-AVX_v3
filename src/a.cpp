#include"DD-AVX.hpp"

int goma(){

	//DD_AVX::dd_scalar a = 1.5;
	dd_real a = 2.0;
	a = cos(a);

	printf("hello world %f\n",a.x[0]);
	return 1;
}
