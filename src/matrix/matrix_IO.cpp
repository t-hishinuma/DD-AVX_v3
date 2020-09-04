#include<DD-AVX_internal.hpp>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <limits>
#include <sstream>

#define MM_BANNER "%%MatrixMarket"
#define MM_MAT "matrix"
#define MM_VEC "vector"
#define MM_FMT "coordinate"
#define MM_TYPE_REAL "real"
#define MM_TYPE_GENERAL "general"
#define MM_TYPE_SYMM "symmetric"

void d_real_SpMat::input_mm(const char* filename){

     std::string banner, buf;
     std::string mm, mat, fmt, dtype, dstruct;

     //file open
     std::ifstream ifs(filename);
     if (!ifs) {
         std::cerr << "Matrix.input: cannot open file " << filename << std::endl;
         std::exit(1);
     }

    //check Matrix Market bannner
    getline(ifs, banner);
    std::istringstream bn(banner);
    bn >> mm >> mat >> fmt >> dtype >> dstruct;

    if (mm != std::string(MM_BANNER)) {
        std::cerr << "Matrix.input: This matrix is not MM format:" << mm << std::endl;
        exit(-1);
    }
    if (mat != std::string(MM_MAT)) {
        std::cerr << "Matrix.input: This matrix is not matrix type:" << mat << std::endl;
        exit(-1);
    }
    if (fmt != std::string(MM_FMT)) {
        std::cerr << "Matrix.input: This matrix is not coodinate format:" << fmt << std::endl;
        exit(-1);
    }
    if (dtype != std::string(MM_TYPE_REAL)) {
        std::cerr << "Matrix.input: This matrix is not real:" << dtype << std::endl;
        exit(-1);
    }
    if (dstruct != std::string(MM_TYPE_GENERAL)) {
        std::cerr << "Matrix.input: This matrix is not general:" << dstruct << std::endl;
        exit(-1);
    }

   //skip %
     do {
         getline(ifs, buf);
     } while (buf[0] == '%');

     //check size
     size_t rowN, colN, NNZ;

     std::istringstream data(buf);
     data >> rowN >> colN >> NNZ;

     //symmetric check!
     if (colN != rowN) {
         std::cerr << "Matrix.input: Matrix is not square" << std::endl;
         exit(-1);
     }
     if (colN <= 0 || NNZ < 0) {
         std::cerr << "Matrix.input: Matrix size should be positive" << std::endl;
         exit(-1);
     }

	 row = rowN;
	 nnz = NNZ;
     val.resize(nnz, 0);
     row_ptr.resize(row+1, 0);
     col_ind.resize(nnz, 0);

	 size_t c_row = 1;
	 row_ptr[0] = 0;
	 //input MM data as selected matrix storage format
 	 for (size_t i = 0; i < NNZ; i++) {
		 size_t idx, jdx;
		 size_t value;

		 getline(ifs, buf);
		 std::istringstream data(buf);
		 data >> idx >> jdx >> value;

         if (idx < 1 || idx > rowN || jdx < 1 || jdx > colN) {
             std::cerr << "Matrix.input: Invalid index" << std::endl;
             exit(1);
         }

		 val[i] = value;
		 col_ind[i] = jdx-1;

		 if(c_row == idx){
			 row_ptr[c_row] = i+1;
		 }
		 else{
			 c_row = c_row + 1;
			 row_ptr[c_row] = i+1;
		 }
      }

     ifs.close();
}

void d_real_SpMat::output(){

	if(row == 0 || nnz == 0){
         std::cerr << "This matrix is brank" << std::endl;
	}

	for(size_t i = 0; i < row; i++){
		for(size_t j = row_ptr[i]; j < row_ptr[i+1]; j++){
			std::cout << i+1 << "\t" << col_ind[j]+1 << "\t" << val[j] << std::endl;
		}
	}
}

void d_real_SpMat::output_mm(const char* filename){

    std::ofstream out(filename);
    out << std::scientific;
    out << std::setprecision(std::numeric_limits<double>::max_digits10);

    out << (MM_BANNER " " MM_MAT " " MM_FMT " " MM_TYPE_REAL " " MM_TYPE_GENERAL) << std::endl;
    out << row << " " << row << " " << nnz << std::endl;

	for(size_t i = 0; i < row; i++){
		for(size_t j = row_ptr[i]; j < row_ptr[i+1]; j++){
			out << i+1 << " " << col_ind[j]+1 << " " << val[j] << std::endl;
		}
	}
}
