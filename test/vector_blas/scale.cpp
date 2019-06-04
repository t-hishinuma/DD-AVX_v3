#include<DD-AVX.hpp>
#include<vector>
#include<iostream>
#define TOL 1.0e-6

std::vector<double> make_ans(double alpha, const std::vector<double>& x){

	std::vector<double> y(x.size(), 0.0);
	#pragma omp parallel for
	for(int i=0; i<y.size(); i++){
		y[i] = alpha * x[i];
	}

	return y;
}

bool err_check(const std::vector<double>& ans, const std::vector<double>& val, const double tol){
	for(int i=0; i<ans.size(); i++){
		double err = fabs((val[i] - ans[i])) / fabs(ans[i]);
		if(err > tol){
			printf("ans[%d] = %e, data[%d] = %e, err = %e\n", i, ans[i], i, val[i], err);
			return false;
		}
	}
	return true;
}

template<typename ALPHA, typename X>
int test(long N)
{
	ALPHA alpha = rand();
	X x;

	for(int i=0; i<N; i++){
		x.push_back(rand());
	}

	auto ref = make_ans(alpha, x.HI());

	dd_avx::scale(alpha, x);

	if(err_check(ref, x.HI(), TOL)){
		std::cout << "pass1" << std::endl;
	}
	else{
		std::cout << "fail1" << std::endl;
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

	std::cout << "DD, DD" << std::endl;
	ret = test<dd_real, dd_real_vector>(N);
	if(ret == false) return ret;

	std::cout << "D, DD" << std::endl;
	ret = test<d_real, dd_real_vector>(N);
	if(ret == false) return ret;

	std::cout << "DD, D" << std::endl;
	ret = test<dd_real, d_real_vector>(N);
	if(ret == false) return ret;

	std::cout << "D, D" << std::endl;
	ret = test<d_real, d_real_vector>(N);
	if(ret == false) return ret;

	return 0;
}

