/*
 * main.cc
 *
 *  Created on: 4 Apr 2017
 *      Author: John
 */

#include <iostream>
#include <array>
#include <string>
#include "constants.h"
#include "indexing.h"
#include "linkclass.h"


int main()
{
  	double latticedata[n];


  	link lattice[n];

 	for (int i=0; i<n; i++){
  		latticedata[i] = i;
  	}
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

  	for(int i=0;i<n;i++) {
  	  	lattice[i].update(0.1);
  	}


  	}





