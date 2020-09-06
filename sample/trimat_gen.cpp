#include<iostream>
#include<stdlib.h>

int main(int argc, char** argv){

	if(argc!=3){
		std::cout << "error, $1 = N, $2 = val" << std::endl;
		return 1;
	}

    int N = atoi(argv[1]);
    double val = atof(argv[2]);

    std::cout << "%%MatrixMarket matrix coordinate real general" << std::endl;
    std::cout << N << " " << N << " " << N*3-2 << std::endl;

    std::cout << 1 << " " << 1 << " " << 3 << std::endl;
    std::cout << 1 << " " << 2 << " " << val << std::endl;

    for(size_t i = 2; i <= N-1; i++){
    std::cout << i << " " << i-1 << " " << val << std::endl;
    std::cout << i << " " << i << " " << 3 << std::endl;
    std::cout << i << " " << i+1 << " " << val << std::endl;
    }

    std::cout << N << " " << N-1 << " " << val << std::endl;
    std::cout << N << " " << N << " " << 3 << std::endl;
}
