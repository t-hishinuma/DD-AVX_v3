#include<stdio.h>
#include"a.hpp"

int goma(){

	dd_real a = 1.5;
	a = cos(a);

	printf("hello world %f\n",a.x[0]);
	return 1;
}
