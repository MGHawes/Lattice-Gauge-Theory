/*
 * setup.cc
 *
 *  Created on: 16 Apr 2017
 *      Author: Matthew
 */

#include "setup.h"
#include <array>
#include <string>
#include "constants.h"
#include "indexing.h"
#include "linkclass.h"
#include "wallclass.h"
#include <utility>
#include "wilsonwall.h"

void setup(double latticedata[n],link lattice[n], twall twallarray[n_t], wilsonwall wwallarray[n_t]){

  	for (int i=0; i<n; i++){
  	  		latticedata[i] = 1;
  	  	}
  	//prepare links
	std::array<int, 4> index;
	for(int mu=0; mu<=2; mu++) {
		index[0] = mu;
		for (int x=0; x<n_x; x++) {
			index[1]=x;
			for (int y=0; y<n_y; y++) {
				index[2]=y;
				for (int t=0; t<n_t; t++) {
					index[3]=t;
					lattice[getindex(index)].initlink(latticedata,index);
				}
			}
		}
	}
	//prepare staples
	for(int mu=0; mu<=2; mu++) {
			index[0] = mu;
			for (int x=0; x<n_x; x++) {
				index[1]=x;
				for (int y=0; y<n_y; y++) {
					index[2]=y;
					for (int t=0; t<n_t; t++) {
						index[3]=t;
						lattice[getindex(index)].setstaples(latticedata,index);
					}
				}
			}
	}

  	//prepare walls
	for (int t=0;t<n_t;t++){
		twallarray[t].inittwall(latticedata,t);
		wwallarray[t].initwwall(latticedata,t);
	}
}

