#include<DD-AVX.hpp>

d_real_vector:: operator dd_real_vector()
{
	printf("cast dd=>d\n");
	dd_real_vector tmp;
	for(long i=0; i<(long)size(); i++){
		tmp.hi[i]=*this[i];
		tmp.lo[i]=0.0;
	}
	return tmp;
}
