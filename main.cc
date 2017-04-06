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
#include <random>
#include <ctime>
#include "wallclass.h"
#include <utility>
#include <algorithm>


  	double latticedata[n];
  	link lattice[n];
  	twall twallarray[n_t];

int main(){

	std::time_t now = time(0);
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
	}


    //initialise gaussian phases set
    //std::random_device gauss_dev;
    std::mt19937 gaussgen(std::time(0));
    std::normal_distribution<double> gaussian(mean,var);

    double phases[2*N_v+1];		//pairs plus the identity
	phases[0] = 0;				//identity
    for (int i=0, j=1;i<N_v;i++){		//iter through N_v times
    	double g = gaussian(gaussgen);
    	phases[j++] = g;				//add the two pairs of phases
    	phases[j++] = -g;				//add the two pairs of phases
    }


  	//declare the rand uniform generators for the metropolis algorithm
//    std::random_device rand_dev;
    std::mt19937 ugen(std::time(0));
    std::uniform_real_distribution<double> uniformdistr(0.0, 1.0);

//    std::random_device int_dev;
    std::mt19937 intgen(std::time(0));
    std::uniform_int_distribution<int> intdistr(0,2*N_v);

    for (int j=1;j<=N_equilib;j++){
		for(int i=0;i<n;i++) {
			lattice[i].update(phases[intdistr(intgen)],uniformdistr(ugen));
		}
		if (j % 100 == 0){
			std::cout<<j<<std::endl;
		}
    }

    std::time_t after = time(0);

    std::cout <<"Equilibriated:"<< after - now << std::endl;
    std::time_t now2 = time(0);


    double avgplaqarray[N_seq];
//    double avgrewall[N_seq][n_t-1];			//store each t array in a particular sequence row
//    double avgimwall[N_seq][n_t-1];

	for (int k=1;k<=N_seq;k++){
		//inside a single sequence of field configs
		double avgplaqsum = 0;
		double rewallseqavg[n_t-1];
		double imwallseqavg[n_t-1];
		std::fill_n(rewallseqavg, n_t-1, 0);
		std::fill_n(imwallseqavg, n_t-1, 0);

		for (int j=1;j<=N_subseq;j++){
		//inside a single field config

			double sumplaq = 0;



			//----------update links--------------
			for(int i=0;i<n;i++) {
				lattice[i].update(phases[intdistr(intgen)],uniformdistr(ugen));
			}

			//----------do operations-------------
			for(int i=0;i<n;i++) {
				sumplaq += lattice[i].getplaqsum();			//add to total sum the sum of plaqs surrounding this link
			}

			double t0rewallavg,t0imwallavg;
			std::pair<double, double> rtnpair = twallarray[0].getvalues();
			t0rewallavg = rtnpair.first;
			t0imwallavg = rtnpair.second;

			std::pair<double, double> looppair;

			for(int t=1;t<n_t;t++){
				looppair = twallarray[t].getvalues();
				rewallseqavg[t-1] += looppair.first * t0rewallavg;
				imwallseqavg[t-1] += looppair.second * t0imwallavg;
			}

			avgplaqsum += sumplaq/(N_plaq * 4);		//divide the sum of all plaqs in the lattice by the number of plaqs and inc the sequence avg

		}

		for(int i=0;i<n_t-1;i++){
			rewallseqavg[i] = rewallseqavg[i]/N_subseq;
			imwallseqavg[i] = imwallseqavg[i]/N_subseq;
		}

		std::cout<<"m_0++ seq"<<k<<":";
		std::cout<< std::endl;
		for(int i=0;i<n_t-1;i++){
			std::cout << rewallseqavg[i]<<", ";
		}
		std::cout<< std::endl;

		std::cout<<"m_0-- seq"<<k<<":";
		std::cout<< std::endl;
		for(int i=0;i<n_t-1;i++){
			std::cout << imwallseqavg[i]<<", ";
		}
		std::cout<< std::endl;

		avgplaqarray[k] = avgplaqsum/N_subseq;
		std::cout <<"Plaqavg:" << avgplaqarray[k] << std::endl;
	}

        double plaqavg = 0;
        double plaqsquaremean = 0;
        for (int k=1;k<=N_seq;k++){
        	plaqavg += avgplaqarray[k];
        	plaqsquaremean += avgplaqarray[k]*avgplaqarray[k];
        }
        plaqsquaremean = plaqsquaremean/N_seq;
        plaqavg = plaqavg/N_seq;
        double plaqsd = std::sqrt(plaqsquaremean - plaqavg*plaqavg);

        std::time_t after2 = time(0);
    std::cout <<"avgplaq:"<<plaqavg<<std::endl;
    std::cout <<"plaqsd:"<<plaqsd<<std::endl;
    std::cout <<"completed in:"<< after2 - now2 << std::endl;
  	}





