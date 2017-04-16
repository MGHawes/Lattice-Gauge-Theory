/*
 * wilsonwall.h
 *
 *  Created on: 16 Apr 2017
 *      Author: Matthew
 */

#ifndef WILSONWALL_H_
#define WILSONWALL_H_
#include "loop.h"
#include <utility>
#include "constants.h"

class wilsonwall {
private:
	loop looparray[n_y];		//loops in the wall

public:
	wilsonwall();

	void initwwall(double _lattice[n], int t);

	std::pair<double, double> getvalues();
};



#endif /* WILSONWALL_H_ */
