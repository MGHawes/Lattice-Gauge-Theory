/*
 * indexing.cc
 *
 *  Created on: 4 Apr 2017
 *      Author: John
 */
#include "indexing.h"
#include "constants.h"

int getindex(std::array<int, 4> _index) {		//check the array passing syntax inc zero or 1 based indexing
	int i = n/3 * _index[0] + ( (_index[1] % n_x) + n_x * ((_index[2] % n_y) + n_y * (_index[3] % n_t))); //check remainder div
	return i;
}


