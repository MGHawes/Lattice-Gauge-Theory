/*
 * indexing.cc
 *
 *  Created on: 4 Apr 2017
 *      Author: John
 */
#include "indexing.h"
#include "constants.h"

int getindex(std::array<int, 4> _index) {		//zero based indexing
	int i = n/3 * _index[0] + ( ((_index[1]+n_x) % n_x) + n_x * (((_index[2]+n_y) % n_y) + n_y * ((_index[3]+n_t) % n_t))); //modulus and '+ n_i' for PBC
	return i;
}

int getplaqindex(std::array<int, 2> _wallindex) {
	int i = ((_wallindex[0]+n_x) % n_x) + n_x * ((_wallindex[1]+n_y) % n_y);
	return i;
}

