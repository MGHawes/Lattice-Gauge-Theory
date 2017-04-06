/*
 * wallclass.cc
 *
 *  Created on: 5 Apr 2017
 *      Author: John
 */

#include <math.h>
#include "indexing.h"
#include "constants.h"
#include "wallclass.h"
#include <utility>
#include "plaqclass.h"

twall::twall(){
	twall::tcoord = 0;

}

void twall::inittwall(double _lattice[n], int t){
	twall::tcoord = t;
	std::array<int, 2> index;

	for (int x=0;x<n_x;x++){
		index[0] = x;
		for (int y=0;y<n_y;y++){
			index[1] = y;
			twall::plaqs[getplaqindex(index)].initplaq(_lattice,x,y,t);
		}
	}
}

std::pair<double, double> twall::getvalues(){			//returns re/im pair of correlators for m0++ and m0-- mass calculations
	double revalue = 0;
	double imvalue = 0;
	std::pair<double, double> valuepair;
	for (int i=0;i<N_plaqintwall;i++){
		valuepair = twall::plaqs[i].getvalues();
		revalue += valuepair.first;
		imvalue += valuepair.second;
	}
	return std::make_pair(revalue, imvalue);
}

void twall::getplaqvals(int x,int y){
	std::array<int, 2> index = {x,y};
	plaqs[getplaqindex(index)].getlinkvals();

}

