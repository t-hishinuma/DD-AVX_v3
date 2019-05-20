#include<DD-AVX.hpp>
dd_real_scalar::dd_real_scalar() {
	x[0] = 0.0;
	x[1] = 0.0;
}

dd_real_scalar::dd_real_scalar(double hi, double lo)
{
	x[0] = hi;
	x[1] = lo;
}

dd_real_scalar::dd_real_scalar(double h){
	x[0] = h;
	x[1] = 0.0;
}

dd_real_scalar::dd_real_scalar(int h) {
	x[0] = (static_cast<double>(h));
	x[1] = 0.0;
}

dd_real_scalar::dd_real_scalar(dd_real a){
	x[0] = a.x[0];
	x[1] = a.x[1];
}

dd_real_scalar::dd_real_scalar(dd_real_vector_ref a){
	x[0] = *a.dd_hi_iter;
	x[1] = *a.dd_hi_iter;
}


dd_real_scalar::operator double(){
	return x[0];
}

// dd_real_scalar::operator dd_real(){
// 	return *this;
// }

dd_real_scalar::operator dd_real_vector_ref(){
// 	dd_real_vector_ref tmp;
// 	*tmp.dd_hi_iter = *this.x[0];
// 	*tmp.dd_lo_iter = *this.x[1];
//	return tmp;
	return *this;
}

///////////////////////////////////////////////////////

void dd_real_scalar::operator=(const dd_real a){
	x[0] = a.x[0];
	x[1] = a.x[1];
}

void dd_real_scalar::operator=(const double a){
	x[0] = a;
	x[1] = 0.0;
}

dd_real_vector::operator std::vector<double>(){
	return hi;
}
dd_real_vector::operator double*(){
	return hi.data();
}

dd_real_vector::operator d_real_vector(){
	printf("cast d=>dd\n");
	return hi;
}

///////////////////////////////////////////////////////

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
