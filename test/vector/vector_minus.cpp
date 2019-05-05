#include<DD-AVX.hpp>
#include<vector>
#include<iostream>
#define TOL 1.0e-8

std::vector<double> make_ans(std::vector<double> vec1){
	std::vector<double> ans(vec1.size(), 0.0);
	#pragma omp parallel for
	for(int i=0; i<ans.size(); i++){
		ans[i] = -1 * vec1[i];
	}
	return ans;
}

bool err_check(const std::vector<double>& ans, const std::vector<double>& val, const double tol){
	for(int i=0; i<ans.size(); i++){
		double err = (val[i] - ans[i]) / ans[i];
		if(err > tol) return false;
	}
	return true;
}

template<typename T>
int test2(long N)
{
//=func()================
	T vec1;
	for(int i=0; i<N; i++)
		vec1.push_back(dd_rand());

	auto ref = make_ans(vec1.HI());

 	vec1.minus(); 

	if(err_check(ref, vec1.HI(), TOL)){
		std::cout << "pass1" << std::endl;
	}
	else{
		std::cout << "fail1" << std::endl;
		return false;
	}

//=operator================================================

	ref = make_ans(vec1.HI());
	vec1 = -vec1;

	if(err_check(ref, vec1.HI(), TOL)){
		std::cout << "pass2" << std::endl;
	}
	else{
		std::cout << "fail2" << std::endl;
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

 	// DD=
	std::cout << "DD = -DD" << std::endl;
	ret = test2<dd_real_vector>(N);
	if(ret == false) return ret;

	// D=
	std::cout << "D = -D" << std::endl;
	ret = test2<d_real_vector>(N);
	if(ret == false) return ret;

	return 0;
}

