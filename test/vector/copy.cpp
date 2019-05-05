#include<DD-AVX.hpp>
#include<vector>
#include<iostream>

template<typename SRC, typename DST>
bool test(long n)
{
		SRC vec1(n, 1.0);
		DST vec2;
		DST vec3(n/2, 5.0);

		vec2.copy(vec1);

 		if(vec1 == vec2){
			std::cout << "pass" << std::endl;
		} 
 		else {
			std::cout << "fail" << std::endl;
			vec2.print_all();
			return false;
		}

		vec3 = vec1;

 		if(vec1 != vec3){
			std::cout << "fail" << std::endl;
			vec3.print_all();
			return false;
		}
		else{
			std::cout << "pass" << std::endl;
		}

		return true;
}
int main(int argc, char** argv){
	bool ret;

	if(argc!=2){
		std::cout << "error, $1 = size" << std::endl;
		return 1;
	}

	long N = atoi(argv[1]);
	std::cout << "size = " << N << std::endl;

	std::cout << "DD = DD" << std::endl;
	ret = test<dd_real_vector, dd_real_vector>(N);
	if(ret == false) return ret;

	std::cout << "D = DD" << std::endl;
	ret = test<dd_real_vector, d_real_vector>(N);
	if(ret == false) return ret;
	
	std::cout << "DD = D" << std::endl;
	ret = test<d_real_vector, dd_real_vector>(N);
	if(ret == false) return ret;

	std::cout << "D = D" << std::endl;
	ret = test<d_real_vector, d_real_vector>(N);
	if(ret == false) return ret;

	return 0;
}

