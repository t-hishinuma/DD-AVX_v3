// dd_real(QD) link test
#include<DD-AVX.hpp>

int main()
{
	dd_real a =1.2;
	dd_real b = 1.2;
	dd_real c = sin(a);

	printf("scalar_test %f %f\n", c.x[0], c.x[1]);
}
