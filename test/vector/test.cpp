#include<DD-AVX.hpp>

int main()
{
	dd_real a =1.2;
	dd_real b = 1.2;
	dd_real c = sin(a);

	dd_real_vector vec;
	dd_real_vector vec2(5);
	dd_real_vector vec3(5, 1.0);

	printf("gomagoma %f\n", c.x[0]);

	goma();
}
