#include<DD-AVX.hpp>
#include<vector>
#include<iostream>

d_real_SpMat make_3dSquare3PointsDirichlet_matrix(int N){
	d_real_SpMat A( N*N*N, N*N*N );
    int d = N;

    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            for (int k = 0; k < d; k++) {
                int p = i * d * d + j * d + k;
                if (i == 0 || i == d - 1 || j == 0 || j == d - 1 | k == 0 || k == d - 1) {
                    A.insert(p, p, 1.0);
                }
				else {
                    A.insert(p, p, -6.0);
                    A.insert(p, i * d * d + j * d + (k + 1), 1.0);
                    A.insert(p, i * d * d + j * d + (k - 1), 1.0);
                    A.insert(p, i * d * d + (j + 1) * d + k, 1.0);
                    A.insert(p, i * d * d + (j - 1) * d + k, 1.0);
                    A.insert(p, (i + 1) * d * d + j * d + k, 1.0);
                    A.insert(p, (i - 1) * d * d + j * d + k, 1.0);
                }
            }
        }
    }
	return A;
}

template<typename FLOAT>
void jacobi(d_real_SpMat A, FLOAT x, FLOAT y)
{
	double tol = 1.0e-12;

	for(int i=0; i<n; i++)
	

}

int main(int argc, char** argv){
	d_real_SpMat A = make_3dSquare3PointsDirichlet_matrix(5);

	//A.output();
	
	d_real_vector x(A.size(), 0.0);
	d_real_vector y(A.size(), 0.0);

	jacobi<d_real_vector, d_real_vector>(A, x, y);

	return 0;
}
