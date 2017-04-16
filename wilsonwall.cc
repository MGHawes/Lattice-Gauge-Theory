/*
 * wilsonwall.cc
 *
 *  Created on: 16 Apr 2017
 *      Author: Matthew
 */

#include "wilsonwall.h"
#include "loop.h"
#include <utility>
#include <cmath>
#include "constants.h"


wilsonwall::wilsonwall(){}

void wilsonwall::initwwall(double _lattice[n], int t){
	for (int y=0;y<n_y;y++){
		wilsonwall::looparray[y].initloop(_lattice,y,t);
	}
}

std::pair<double, double> wilsonwall::getvalues(){
	double cosloop = 0;
	double sinloop = 0;
	for (int y=0;y<n_y;y++){
		double phasesum = wilsonwall::looparray[y].getvalue();
		cosloop += std::cos(phasesum);
		sinloop += std::sin(phasesum);
	}
	return std::make_pair(cosloop, sinloop);
}

