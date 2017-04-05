/*
 * plaqclass.cc
 *
 *  Created on: 5 Apr 2017
 *      Author: John
 */
#include "indexing.h"
#include <cmath>
#include <array>
#include <utility>
#include <iostream>
#include "constants.h"
#include "plaqclass.h"

plaq::plaq(){
	for (int i=0; i<=4; i++) {
		plaq::_links[i] = NULL;
	}
}

void plaq::initplaq(double _lattice[n],int x,int y,int t){
	std::array<int, 4> index;
	//start with xlink
	index[0] = 0;
	index[1] = x;
	index[2] = y;
	index[3] = t;
	plaq::_links[0] = &_lattice[getindex(index)];	//store address of lattice in pointer _links[0]
	index[0] = 1;	//switch to ylink
	plaq::_links[3] = &_lattice[getindex(index)];
	//hop fwd in x, still want ylink
	index[1] += 1;
	plaq::_links[1] = &_lattice[getindex(index)];
	//hop back in x and up in y then switch to xlink
	index[1] -= 1;
	index[2] += 1;
	index[0] = 0;
	plaq::_links[2] = &_lattice[getindex(index)];
}

std::pair<double, double> plaq::getvalues(){
	double replaq = 0;
	double implaq = 0;
	double phaseloop = *plaq::_links[0] + *plaq::_links[1] - *plaq::_links[2] - *plaq::_links[3];
	replaq =  std::cos(phaseloop)-avgplaqconst;
	implaq =  std::sin(phaseloop);

	return std::make_pair(replaq, implaq);
}

void plaq::getlinkvals(){
	for (int i=0;i<4;i++){
		std::cout<<*plaq::_links[i]<<" ";
	}
	std::cout<<std::endl;
}


