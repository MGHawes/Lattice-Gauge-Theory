/*
 * loop.h
 *
 *  Created on: 16 Apr 2017
 *      Author: Matthew
 */

#ifndef LOOP_H_
#define LOOP_H_
#include "constants.h"

class loop {
	private:
		double *_linkarray[n_x];

	public:
		loop();

		void initloop(double _lattice[n], int y, int t);

		double getvalue();
};



#endif /* LOOP_H_ */
