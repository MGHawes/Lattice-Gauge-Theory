/*
 * constants.h
 *
 *  Created on: 4 Apr 2017
 *      Author: John
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

const double pi = 3.14159265359;

const double beta = 2.2;

const int n_dir = 3;
const int n_x = 10;
const int n_y = 10;
const int n_t = 10;
const int n = n_dir * n_x * n_y * n_t;			//n is no. of links
const int N_plaq = n; 							//no. plaqs is the same as the no. of links

const double mean = 0;
const double var = 0.75;
const int N_v = 200;

const int N_equilib = 1000;
const int N_subseq = 500;



#endif /* CONSTANTS_H_ */
