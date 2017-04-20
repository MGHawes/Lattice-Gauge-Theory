/*
 * stapleclass.cc
 *
 *  Created on: 4 Apr 2017
 *      Author: John
 */
#include "stapleclass.h"
#include "indexing.h"
#include <cstddef>

staple::staple() {		//index passed by value
	staple::dir = 0;
	for (int i=0; i<3; i++) {
		staple::_links[i] = NULL;
	}
}

void staple::initstaple(int x, double _lattice[n],std::array<int, 4> _index, int lambda) {		//index passed by value
	staple::dir = x;
	int mu = _index[0];
	if (staple::dir == 1) {
		_index[0] = lambda;
		staple::_links[2] = &_lattice[getindex(_index)];	//set pointer to point to appropriate link
		_index[mu+1] += 1;		//increment the mu-staple::dir coordinate by one
		staple::_links[0] = &_lattice[getindex(_index)];
		_index[0] = mu;
		_index[mu+1] -= 1;
		_index[lambda+1] += 1;
		staple::_links[1] = &_lattice[getindex(_index)];
	} else { if (staple::dir == -1) {
		_index[lambda+1] -= 1;
		staple::_links[1] = &_lattice[getindex(_index)];
		_index[0] = lambda;
		staple::_links[2] = &_lattice[getindex(_index)];
		_index[mu+1] += 1;
		staple::_links[0] = &_lattice[getindex(_index)];
			}
		}
	}

double **staple::getvalues(){		//double derefernce, pointer to array of pointers
	return staple::_links;
}

double staple::getvalue() {
	if (staple::dir == 1) {
		return *staple::_links[0] - *staple::_links[1] - *staple::_links[2];	//deref each of the three pointers to get staple
	} else {return *staple::_links[2] - *staple::_links[0] - *staple::_links[1]; }
}



