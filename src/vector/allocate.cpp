#include"DD-AVX.hpp"

void dd_real_vector::resize(long n){
	N=n;
	hi.resize(N);
	lo.resize(N);
}

void dd_real_vector::resize(long n, double val){
	N=n;
	hi.resize(N, val);
	lo.resize(N, 0.0);
};

void dd_real_vector::resize(long n, dd_real val){
	N=n;
	hi.resize(N, val.x[0]);
	lo.resize(N, val.x[1]);
};

void dd_real_vector::push_back(const double val){
	N=N+1;
	hi.push_back(val);
	lo.push_back(0.0);
}

void dd_real_vector::push_back(const dd_real val){
	N=N+1;
	hi.resize(val.x[0]);
	lo.resize(val.x[1]);
}
