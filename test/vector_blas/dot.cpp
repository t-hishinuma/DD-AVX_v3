#include<DD-AVX.hpp>
#include<vector>
#include<iostream>
#include<random>
#define TOL 1.0e-4

double make_ans(const std::vector<double> x, const std::vector<double>& y){

	double dot = 0;
	for(int i=0; i<y.size(); i++){
		dot += x[i] * y[i];
	}
	return dot;
}



bool err_check(double ans, double val, const double tol){

	double err = fabs((val - ans)) / fabs(ans);
	if(err > tol){
		printf("ans[%d] = %e, data[%d] = %e, err = %e\n", 0, ans, 0, val, err);
		return false;
	}
	return true;
}

template<typename ALPHA, typename X, typename Y>
int test(long N)
{
	ALPHA alpha = 0;
	X x;
	Y y;

	for(int i=0; i<N; i++){
		x.push_back(rand());
		y.push_back(rand());
    }


	alpha = dd_avx::dot(x, y);

	auto ref = make_ans(x.HI(), y.HI());

	if(err_check(ref, (d_real&)alpha, TOL)){
		std::cout << "pass" << std::endl;
	}
	else{
		std::cout << "fail" << std::endl;
		return false;
	}

	return true;
}

int main(int argc, char** argv){
	bool ret=0;

	if(argc!=2){
		std::cout << "error, $1 = size" << std::endl;
		return 1;
	}

	long N = atoi(argv[1]);
	std::cout << "size = " << N << std::endl;

	std::cout << "DD, DD, DD" << std::endl;
	ret = test<dd_real, dd_real_vector, dd_real_vector>(N);
	if(!ret) return 1;

	std::cout << "DD, D, DD" << std::endl;
	ret = test<dd_real, d_real_vector, dd_real_vector>(N);
	if(!ret) return 1;

	std::cout << "DD, D, DD" << std::endl;
	ret = test<dd_real, d_real_vector, dd_real_vector>(N);
	if(!ret) return 1;

	std::cout << "DD, D, D" << std::endl;
	ret = test<dd_real, d_real_vector, d_real_vector>(N);
	if(!ret) return 1;

	std::cout << "D, DD, DD" << std::endl;
	ret = test<d_real, dd_real_vector, dd_real_vector>(N);
	if(!ret) return 1;

	std::cout << "D, DD, D" << std::endl;
	ret = test<d_real, dd_real_vector, d_real_vector>(N);
	if(!ret) return 1;

	std::cout << "D, D, DD" << std::endl;
	ret = test<d_real, d_real_vector, dd_real_vector>(N);
	if(!ret) return 1;

	std::cout << "D, D, D" << std::endl;
	ret = test<d_real, d_real_vector, d_real_vector>(N);
	if(!ret) return 1;

	return 0;
}

