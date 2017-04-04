/*
 * linkclass.h
 *
 *  Created on: 4 Apr 2017
 *      Author: John
 */

#ifndef LINKCLASS_H_
#define LINKCLASS_H_

#include <math.h>
#include "stapleclass.h"
#include "constants.h"
#include <array>

class link {
private:
	double *_value;		//pointer to link value
	staple _staples[4];	//array of staple pointers, check syntax, check how james parses


public:
	link();

	void initlink(double _lattice[n], std::array<int, 4> _index);

	double getvalue();

	void getstaples();

	void getstaplessilent();

	void setvalue(double val);

	double getaction(double linkval);

	void update(double val);

	void setstaples(double _lattice[n],std::array<int, 4> _index);
};



#endif /* LINKCLASS_H_ */
