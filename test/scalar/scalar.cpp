// dd_real(QD) link test
#include<DD-AVX.hpp>

int main()
{
	dd_real dd = 1.5;
	dd_real a =1.2;
	dd_real b = 1.2;
	dd_real c = sin(a);
	dd_real d = dd;

	dd_real xx = d;
	dd_real zz = 1.0;

	dd_real yy = 1;
	xx = zz * yy + xx + yy / zz;

	printf("scalar_test %f %f\n", c.x[0], c.x[1]);
}
