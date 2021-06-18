#include<DD-AVX.hpp>
#include<vector>
#include<iostream>

int main()
{
	dd_real a =1.2;
	dd_real b = 1.2;
	dd_real c = sin(a);

	dd_real_vector ddvec1(10, 1.0);
	dd_real_vector ddvec2(5);
	dd_real_vector ddvec3;

	printf("initialization test...\n");

	printf("ddvec1: size=%d\n", ddvec1.size());
	printf("ddvec2: size=%d\n", ddvec2.size());
	printf("ddvec3: size=%d\n", ddvec3.size());


	ddvec2.resize(100);
	ddvec3.resize(200, 123.0);

	printf("resize test...\n");

	printf("ddvec1: size = %d, [0] = %f\n", ddvec1.size(), (double)ddvec1[0]);
	printf("ddvec2: size = %d, [0] = %f\n", ddvec2.size(), (double)ddvec2[0]);
	printf("ddvec3: size = %d, [0] = %f\n", ddvec3.size(), (double)ddvec3[0]);

	ddvec1.push_back(321);
	ddvec2.push_back(a);

	ddvec1.print_all();

 	std::cout << (double)ddvec1[10] << std::endl;
 	printf("ddvec1: size = %d, [11] = %f\n", ddvec1.size(), (double)ddvec1[10]);
 	printf("ddvec2: size = %d, [101] = %f\n", ddvec2.size(), (double)ddvec2[100]);

	dd_real x = ddvec1.at(0);
	dd_real y = ddvec1[0];
 	std::cout << "at function\t" << x << "\t" << y << std::endl;

// 	printf("%f",a.x[0]);


	//printf("vec3[0] = %f", vec3.hi[0]);

// 	vec1.resize(100);
// 	printf("vec1: size=%d\n", vec1.size());


	//vec2[0] = a;
	//printf("vec2[0]=%f\n", (double)vec2[0]);

	//printf("vec2[0]=%f\n", (double)vec2.hi[0]);

}
