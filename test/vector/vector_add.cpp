#include<DD-AVX.hpp>
#include<vector>
#include<iostream>

std::vector<double> ans(std::vector<double> vec1, std::vector <double> vec2){
	std::vector<double> ans(vec1.size(), 0.0);
	#pragma omp parallel for
	for(int i=0; i<ans.size(); i++){
		ans[i] = vec1[i] + vec2[i];
	}
	return ans;
}

bool err_check(std::vector<double> ans, std::vector <double> val, double tol){
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
	vec1.print_all();
	printf("%d, %d", vec1.size(), vec2.size());
	printf("================\n");
 	vec1.add(vec1, vec2);
	vec1.print_all();

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

