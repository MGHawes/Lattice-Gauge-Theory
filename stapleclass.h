/*
 * stapleclass.h
 *
 *  Created on: 4 Apr 2017
 *      Author: John
 */

#ifndef STAPLECLASS_H_
#define STAPLECLASS_H_
#include <array>
#include "constants.h"

class staple {			//staples belong to links to is no notion of an array of staples
	private:
		double *_links[3];		//init array of pointers, remember to dereference when you want the variable
		int dir;

	public:
		staple();

		void initstaple(int x, double _lattice[n],std::array<int, 4> _index, int lambda = 100);

		double **getvalues() ;

		double getvalue();
};



#endif /* STAPLECLASS_H_ */
