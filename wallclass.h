/*
 * wallclass.h
 *
 *  Created on: 5 Apr 2017
 *      Author: John
 */

#ifndef WALLCLASS_H_
#define WALLCLASS_H_

#include <array>
#include "plaqclass.h"
#include <utility>

class twall {
private:
	int tcoord;		//'n_t' coordinate of the wall
	plaq plaqs[N_plaqintwall];	//array of plaqs in wall


public:
	twall();

	void inittwall(double _lattice[n], int t);

	std::pair<double, double> getvalues();

	void getplaqvals(int x,int y);
};



#endif /* WALLCLASS_H_ */
