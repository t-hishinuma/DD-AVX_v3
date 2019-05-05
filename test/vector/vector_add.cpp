#include<DD-AVX.hpp>
#include<vector>
#include<iostream>
#define TOL 1.0e-8

std::vector<double> ans(const std::vector<double>& vec1, const std::vector<double>& vec2){
	std::vector<double> ans(vec1.size(), 0.0);
	#pragma omp parallel for
	for(int i=0; i<ans.size(); i++){
		ans[i] = vec1[i] + vec2[i];
	}
	return ans;
}

bool err_check(const std::vector<double>& ans, const std::vector<double>& val, const double tol){
	for(int i=0; i<ans.size(); i++){
		double err = (val[i] - ans[i]) / ans[i];
		if(err < tol) return false;
	}
	return true;
}

template<typename SRC, typename DST>
int test2()
{
	SRC vec1;
	for(int i=0; i<10; i++)
		vec1.push_back(dd_rand());

 	DST vec2(10, 1.0e+9);

 	vec1.add(vec1, vec2); //lib

	std::vector<double> ans = ans(vec1.hi, vec2.hi);

	if(err_check(ans, vec1.data(), TOL)){
		return true;
	}
	else{
		vec1.print_all();
		return false;
	}

	return 0;
}
int main(){
	int ret=0;

	std::cout << "DD = DD" << std::endl;
	ret = test2<dd_real_vector, dd_real_vector>();
	if(ret == 1) return ret;
//
// 	std::cout << "D = DD" << std::endl;
// 	ret = test2<dd_real_vector, d_real_vector>();
// 	if(ret == 1) return ret;
//
// 	std::cout << "DD = D" << std::endl;
// 	ret = test2<d_real_vector, dd_real_vector>();
// 	if(ret == 1) return ret;
//
// 	std::cout << "D = D" << std::endl;
// 	ret = test2<d_real_vector, d_real_vector>();
// 	if(ret == 1) return ret;

	return ret;
}

