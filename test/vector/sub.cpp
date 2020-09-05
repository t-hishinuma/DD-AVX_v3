#include<DD-AVX.hpp>
#include<vector>
#include<iostream>
#include<chrono>
#define TOL 1.0e-8

std::vector<double> make_ans(std::vector<double> vec1, std::vector<double> vec2){
	std::vector<double> ans(vec1.size(), 0.0);
	#pragma omp parallel for
	for(int i=0; i<ans.size(); i++){
		ans[i] = vec1[i] - vec2[i];
	}
	return ans;
}

bool err_check(const std::vector<double>& ans, const std::vector<double>& val, const double tol){
	for(int i=0; i<ans.size(); i++){
		double err = fabs(val[i] - ans[i]) / fabs(ans[i]);
		if(err > tol){
			printf("ans[%d] = %e, data[%d] = %e, err = %e\n", i, ans[i], i, val[i], err);
			return false;
		}
	}
	return true;
}

template<typename DST, typename SRC1, typename SRC2>
int test(long N)
{
//=func()================
	DST vec1;
	for(int i=0; i<N; i++)
		vec1.push_back(rand());

 	SRC1 vec2(N, 1.0e+9);
 	SRC2 vec3(N, 2.0e+9);

	auto ref = make_ans(vec2.HI(), vec3.HI());

 	vec1.sub(vec2, vec3); 

	if(!err_check(ref, vec1.HI(), TOL)){
		std::cout << "...fail1" << std::endl;
		return false;
	}
//=operator================================================
	ref = make_ans(vec2.HI(), vec3.HI());
	vec1 = vec2 - vec3; 

	if(!err_check(ref, vec1.HI(), TOL)){
		std::cout << "...fail2" << std::endl;
		return false;
	}
//=operator================================================
	ref = make_ans(vec1.HI(), vec2.HI());
	vec1 -= vec2;

	if(!err_check(ref, vec1.HI(), TOL)){
		std::cout << "...fail3" << std::endl;
		return false;
	}

	auto start = std::chrono::system_clock::now();
    for(int i=0; i<100; i++)
 	    vec1.sub(vec2, vec3); 
	auto end = std::chrono::system_clock::now();
	double sec = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()/1.0e+9/100;

	std::cout << "...pass\t" << sec << std::endl;


	return true;
}

int main(int argc, char** argv){
	bool ret=0;

	if(argc!=2){
		std::cout << "error, $1 = size" << std::endl;
		return 1;
	}

	long N = atoi(argv[1]);
	std::cout << "sub, size = " << N << std::endl;

 	// DD=
	std::cout << "DD = DD - DD" << std::flush;
	ret = test<dd_real_vector, dd_real_vector, dd_real_vector>(N);
	if(!ret) return 1;

	std::cout << "DD = DD - D" << std::flush;
	ret = test<dd_real_vector, dd_real_vector, d_real_vector>(N);
	if(!ret) return 1;

	std::cout << "DD = D - DD" << std::flush;
	ret = test<dd_real_vector, d_real_vector, dd_real_vector>(N);
	if(!ret) return 1;

	std::cout << "DD = D - D" << std::flush;
	ret = test<dd_real_vector, d_real_vector, d_real_vector>(N);
	if(!ret) return 1;

	// D=
	std::cout << "D = DD - DD" << std::flush;
	ret = test<d_real_vector, dd_real_vector, dd_real_vector>(N);
	if(!ret) return 1;

	std::cout << "D = DD - D" << std::flush;
	ret = test<d_real_vector, dd_real_vector, d_real_vector>(N);
	if(!ret) return 1;

	std::cout << "D = D - DD" << std::flush;
	ret = test<d_real_vector, d_real_vector, dd_real_vector>(N);
	if(!ret) return 1;

	std::cout << "D = D - D" << std::flush;
	ret = test<d_real_vector, d_real_vector, d_real_vector>(N);
	if(!ret) return 1;

	return 0;
}

