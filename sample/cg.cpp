#include<DD-AVX.hpp>
#include<vector>
#include<iostream>
#include<chrono>
#define TOL 1.0e-6

int main(int argc, char** argv){
	bool ret=0;

	if(argc!=2){
		std::cout << "error, $1 = matrix file" << std::endl;
		return 1;
	}

	d_real_SpMat A;
	A.input_mm(argv[1]);

 	dd_real_vector x(A.get_row(), 123.0);

 	dd_real_vector ans(A.get_row(), 1.0);
 	dd_real_vector b(A.get_row(), 0.0);

    dd_avx::matvec(A, ans, b); // b = A*1

 	dd_real_vector r(A.get_row(), 0.0);
 	dd_real_vector rold(A.get_row(), 0.0);
 	dd_real_vector p(A.get_row(), 0.0);
 	dd_real_vector q(A.get_row(), 0.0);

    dd_avx::matvec(A, x, q);
	r = b - q;

	//p0 = Mr0
	p = r;

    //for(size_t iter = 0; iter < A.get_row(); iter++)
    for(size_t iter = 0; iter < A.get_row(); iter++)
    {
        dd_avx::matvec(A,p,q);

        auto tmp = dd_avx::dot(r,r);
        auto alpha = tmp / dd_avx::dot(p,q);

        dd_avx::axpy(alpha, p, x);

        dd_avx::axpy(-alpha, q, r);

        auto beta = dd_avx::dot(r,r) / tmp;

        dd_avx::xpay(beta, r, p); //p = r + beta*p

        double resid = dd_avx::nrm2(r);
        printf("%e\n", resid);

        if( resid < 1.0e-12){
            printf("iter: %ld\n", iter);
            return 0;
        } 
    }

	return 1;
}

