#include<DD-AVX.hpp>
#include<vector>
#include<iostream>
#define TOL 1.0e-6

std::vector<double> make_ans(const double alpha, const std::vector<double>& x){
	std::vector<double> y(x.size(), 0.0);
	#pragma omp parallel for
	for(int i=0; i<y.size(); i++){
		y[i] = alpha * x[i] + y[i];
//		printf("%d:: %e, %e, %e\n", i, alpha, x[i], y[i]);
	}
	return y;
}

std::vector<double> make_ans(const dd_real alpha, const std::vector<double>& x){
	std::vector<double> y(x.size(), 0.0);
	#pragma omp parallel for
	for(int i=0; i<y.size(); i++){
		y[i] = alpha.x[0] * x[i] + y[i];
//		printf("%d:: %e, %e, %e\n", i, alpha, x[i], y[i]);
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

template<typename ALPHA, typename X, typename Y>
int test(long N)
{
	ALPHA alpha = rand();
	X x;
	Y y;

	for(int i=0; i<N; i++)
		x.push_back(rand());

	for(int i=0; i<N; i++)
		y.push_back(rand());

	dd_avx::axpy(alpha, x, y);

	auto ref = make_ans(alpha, x.HI());

	if(err_check(ref, y.HI(), TOL)){
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

// 	if(argc!=2){
// 		std::cout << "error, $1 = size" << std::endl;
// 		return 1;
// 	}

	d_real_SpMat A;
	A.input_mm("./test.mtx");

	dd_real_vector x(A.get_row(), 1.0);
	dd_real_vector y(A.get_row(), 0.0);

	dd_avx::matvec(A, x, y);

	y.print_all();


	return 0;
}

