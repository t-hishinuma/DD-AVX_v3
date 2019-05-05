#include<DD-AVX.hpp>
#include<vector>
#include<iostream>
#define TOL 1.0e-8

std::vector<double> make_ans(std::vector<double> vec1, std::vector<double> vec2){
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
		if(err > tol) return false;
	}
	return true;
}

template<typename DST, typename SRC1, typename SRC2>
int test2()
{
//=func()================
	DST vec1;
	for(int i=0; i<10; i++)
		vec1.push_back(dd_rand());

 	SRC1 vec2(10, 1.0e+9);
 	SRC2 vec3(10, 2.0e+9);

	std::vector<double> ref;
	ref = make_ans(vec2.HI(), vec3.HI());

 	vec1.add(vec2, vec3); 

	if(err_check(ref, vec1.HI(), TOL)){
		std::cout << "pass" << std::endl;
	}
	else{
		std::cout << "fail" << std::endl;
		for(int i=0; i< ref.size(); i++)
			std::cout << i << ", ans:" << ref[i] << ", data:" << vec1.hi[i] << std::endl;
		return false;
	}
//=operator================================================
	ref = make_ans(vec2.HI(), vec3.HI());
	vec1 = vec2 + vec3;

	if(err_check(ref, vec1.HI(), TOL)){
		std::cout << "pass" << std::endl;
	}
	else{
		std::cout << "fail" << std::endl;
		for(int i=0; i< ref.size(); i++)
			std::cout << i << ", ans:" << ref[i] << ", data:" << vec1.hi[i] << std::endl;
		return false;
	}
//=operator================================================
	ref = make_ans(vec1.HI(), vec2.HI());
	vec1 += vec2;

	if(err_check(ref, vec1.HI(), TOL)){
		std::cout << "pass" << std::endl;
	}
	else{
		std::cout << "fail" << std::endl;
		for(int i=0; i< ref.size(); i++)
			std::cout << i << ", ans:" << ref[i] << ", data:" << vec1.hi[i] << std::endl;
		return false;
	}

	return true;
}
int main(){
	bool ret=0;

	std::cout << "DD = DD + DD" << std::endl;
	ret = test2<dd_real_vector, dd_real_vector, dd_real_vector>();
	if(ret == false) return ret;

	std::cout << "D = DD + D" << std::endl;
	ret = test2<dd_real_vector, dd_real_vector, d_real_vector>();
	if(ret == false) return ret;
//
// 	std::cout << "DD = DD + D" << std::endl;
// 	ret = test2<dd_real_vector, dd_real_vector, d_real_vector>();
// 	if(ret == 1) return ret;

// 	std::cout << "D = D + D" << std::endl;
// 	ret = test2<dd_real_vector, d_real_vector, d_real_vector>();
// 	if(ret == 1) return ret;
//
// 	std::cout << "D = D" << std::endl;
// 	ret = test2<d_real_vector, d_real_vector>();
// 	if(ret == 1) return ret;

	return 0;
}

