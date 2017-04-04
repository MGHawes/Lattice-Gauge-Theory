/*
 * linkclass.cc
 *
 *  Created on: 4 Apr 2017
 *      Author: John
 */

#include "linkclass.h"
#include <iostream>
#include "constants.h"
#include "indexing.h"
#include "stapleclass.h"


link::link() {
	link::_value = NULL;
}

void link::initlink(double _lattice[n], std::array<int, 4> _index) {		//lattice is a single pointer, _index = {mu, x, y, z}
	link::_value = &_lattice[getindex(_index)];     //value contains the addr of the value
}

double link::getvalue() {
		return *link::_value;
}

void link::getstaples() {
	for (int i=0;i<4;i++){
		double** stplarray;
		stplarray = link::_staples[i].getvalues();
		for (int j=0;j<3;j++){
			std::cout<<*stplarray[j]<<" ";
			}
			std::cout<<std::endl;
		};
	}
void link::getstaplessilent() {
	for (int i=0;i<4;i++){
		double** stplarray;
		stplarray = link::_staples[i].getvalues();
		for (int j=0;j<3;j++){
			if (*stplarray[j] == -1){
				std::cout<<"oh dear!";
			}
			}
		}
	}
void link::setvalue(double val) {
	*link::_value = val;
}

double link::getaction(double linkval) {
	double action = 0;
	for (int i=0;i<4;i++){
		action += - std::cos(link::_staples[i].getvalue()+*link::_value); //action takes the minus value S=\sum_p 1-Re(U_p)
	}
	return action;
}

void link::update(double newval) {		//attempt to update the link value to 'newval'
		;
	}

void link::setstaples(double _lattice[n],std::array<int, 4> _index) {
	for(int loopi=0, staplesi=0; loopi<=2; loopi++) {
		if (_index[0] != loopi) {
			link::_staples[staplesi++].initstaple(1, _lattice, _index, loopi);
			link::_staples[staplesi++].initstaple(-1, _lattice, _index, loopi); //opposite dir
		}
	}
}



