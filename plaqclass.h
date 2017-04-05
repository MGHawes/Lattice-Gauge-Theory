/*
 * plaqclass.h
 *
 *  Created on: 5 Apr 2017
 *      Author: John
 */
#ifndef PLAQCLASS_H_
#define PLAQCLASS_H_

class plaq {			//staples belong to links to is no notion of an array of staples
	private:
		double *_links[4];		//init array of pointers, remember to dereference when you want the variable

	public:
		plaq();

		void initplaq(double _lattice[n],int x,int y,int t);

		std::pair<double, double> getvalues();

		void getlinkvals();
};

#endif

