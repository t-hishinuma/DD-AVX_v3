#include<DD-AVX.hpp>
//Double
//==
bool d_real_vector::operator==(const dd_real_vector& vec){
	bool ret = ((size_t)size() == (size_t)vec.size());
	if(ret == false) return false;

	ret = ret && std::equal(vec.hi.cbegin(), vec.hi.cend(), cbegin());
	return ret;
}

bool d_real_vector::operator==(const d_real_vector& vec){
	bool ret = ((size_t)size() == (size_t)vec.size());
	if(ret == false) return false;

	ret = ret && std::equal(vec.cbegin(), vec.cend(), cbegin());
	return ret;
}

bool d_real_vector::operator==(const std::vector<double>& vec){
	bool ret = ((size_t)size() == (size_t)vec.size());
	if(ret == false) return false;

	ret = ret && std::equal(vec.cbegin(), vec.cend(), cbegin());
	return ret;
}

bool d_real_vector::operator==(const std::vector<dd_real>& vec){
	bool ret = ((size_t)size() == (size_t)vec.size());
	if(ret == false) return false;

//	#pragma omp parallel for 
	for(size_t i=0; i < (size_t)vec.size(); i++){
		ret = ret && at(i) == vec[i].x[0];
		if(ret == false) return ret;
	}

	return ret;
}

//!=
bool d_real_vector::operator!=(const dd_real_vector& vec){
	bool ret = (*this == vec);
	return !ret;
}

bool d_real_vector::operator!=(const d_real_vector& vec){
	bool ret = (*this == vec);
	return !ret;
}

bool d_real_vector::operator!=(const std::vector<double>& vec){
	bool ret = (*this == vec);
	return !ret;
}

bool d_real_vector::operator!=(const std::vector<dd_real>& vec){
	bool ret = (*this == vec);
	return !ret;
}

//DD
//==
bool dd_real_vector::operator==(const dd_real_vector& vec){
	bool ret = (size() == (size_t)vec.size());
	if(ret == false) return false;

	ret = ret && std::equal(vec.hi.cbegin(), vec.hi.cend(), hi.cbegin());
	ret = ret && std::equal(vec.lo.cbegin(), vec.lo.cend(), lo.cbegin());
	return ret;
}

bool dd_real_vector::operator==(const d_real_vector& vec){
	bool ret = (size() == (size_t)vec.size());
	if(ret == false) return false;

	ret = ret && std::equal(vec.cbegin(), vec.cend(), hi.cbegin());
	return ret;
}

bool dd_real_vector::operator==(const std::vector<double>& vec){
	bool ret = (size() == (size_t)vec.size());
	if(ret == false) return false;

	ret = ret && std::equal(vec.cbegin(), vec.cend(), hi.cbegin());
	return ret;
}

bool dd_real_vector::operator==(const std::vector<dd_real>& vec){
	bool ret = (size() == (size_t)vec.size());
	if(ret == false) return false;

//	#pragma omp parallel for 
	for(size_t i=0; i < (size_t)vec.size(); i++){
		ret = ret && hi[i] == vec[i].x[0] && lo[i] == vec[i].x[1];
		if(ret == false) return ret;
	}

	return ret;
}
//!=
bool dd_real_vector::operator!=(const dd_real_vector& vec){
	bool ret = (*this == vec);
	return !ret;
}

bool dd_real_vector::operator!=(const d_real_vector& vec){
	bool ret = (*this == vec);
	return !ret;
}

bool dd_real_vector::operator!=(const std::vector<double>& vec){
	bool ret = (*this == vec);
	return !ret;
}

bool dd_real_vector::operator!=(const std::vector<dd_real>& vec){
	bool ret = (*this == vec);
	return !ret;
}
