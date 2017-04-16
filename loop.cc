/*
 * loop.cc
 *
 *  Created on: 16 Apr 2017
 *      Author: Matthew
 */

#include "loop.h"
#include "indexing.h"
#include <array>
#include "constants.h"

loop::loop(){
	for (int x=0; x<n_x; x++) {
		loop::_linkarray[x] = NULL;
	}
}

void loop::initloop(double _lattice[n], int y, int t) {
	std::array<int, 4> index;
	index[0] = 0;
	index[2] = y;
	index[3] = t;
	for (int x=0;x<n_x;x++){
		index[1] = x;
		int ind  = getindex(index);
		loop::_linkarray[x] = &_lattice[ind];
	}
}

double loop::getvalue(){
	double result = 0;
	for (int x=0;x<n_x;x++){
		result += *loop::_linkarray[x];
	}
	return result;
}



