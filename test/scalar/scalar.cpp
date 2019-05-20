// dd_real(QD) link test
#include<DD-AVX.hpp>

int main()
{
	dd_real dd = 1.5;
	dd_real_scalar a =1.2;
	dd_real_scalar b = 1.2;
	dd_real_scalar c = sin(a);
	dd_real_scalar d = dd;

	dd_real_scalar xx = d;
	dd_real_scalar zz = 1.0;

	dd_real yy = 1;
	xx = zz * yy + xx + yy / zz;

	printf("scalar_test %f %f\n", c.x[0], c.x[1]);
}
