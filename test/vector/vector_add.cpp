#include<DD-AVX.hpp>
#include<vector>
#include<iostream>

	template<typename SRC, typename DST>
int test2()
{
	SRC vec1;
	DST vec2;
	DST vec3;

	vec2.copy(vec1);
	vec2.add(vec1, vec2);

	if(vec1 == vec2){
		std::cout << "pass" << std::endl;
	} 
	else {
		vec2.print_all();
		return 1;
	}

	vec3 = vec1;

	if(vec1 != vec3){
		vec3.print_all();
		return 1;
	}
	else{
		std::cout << "pass" << std::endl;
	}

	return 0;
}
int main(){
	int ret=0;

	std::cout << "DD = DD" << std::endl;
	ret = test2<dd_real_vector, dd_real_vector>();
	if(ret == 1) return ret;

	std::cout << "D = DD" << std::endl;
	ret = test2<dd_real_vector, d_real_vector>();
	if(ret == 1) return ret;

	std::cout << "DD = D" << std::endl;
	ret = test2<d_real_vector, dd_real_vector>();
	if(ret == 1) return ret;

	std::cout << "D = D" << std::endl;
	ret = test2<d_real_vector, d_real_vector>();
	if(ret == 1) return ret;

	return ret;
}

