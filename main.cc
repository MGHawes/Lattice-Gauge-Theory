/*
 * main.cc
 *
 *  Created on: 4 Apr 2017
 *      Author: John
 */

#include <iostream>
#include <sstream>
#include <fstream>
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

	std::string fname;
	std::stringstream fnamestream;
	std::ofstream outfile;

	fnamestream << "lgt"<< n_x << n_y << n_t << N_equilib << N_subseq<< ".txt";
	fname = fnamestream.str();

	outfile.open(fname);

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

    int acceptances = 0;
    int tries = 0;

    for (int j=1;j<=N_equilib;j++){
		for(int i=0;i<n;i++) {
			acceptances += lattice[i].update(phases[intdistr(intgen)],uniformdistr(ugen));
			tries += 1;
		}
		if (j % 100 == 0){
			std::cout<<j<<std::endl;
			std::cout << "Acceptances: "<<acceptances<<"/"<<tries<< std::endl;
			acceptances = 0;
			tries = 0;
		}
    }

    std::time_t after = time(0);

    std::cout <<"Equilibriated:"<< after - now << std::endl;
    outfile <<"Equilibriated:"<< after - now << std::endl;
    std::time_t now2 = time(0);


    double avgplaqarray[N_seq];
//    double avgrewall[N_seq][n_t-1];			//store each t array in a particular sequence row
//    double avgimwall[N_seq][n_t-1];

	for (int k=1;k<=N_seq;k++){
		//inside a single sequence of field configs
		double avgplaqsum = 0;
		double rewallseqavg[n_t-1];
		double imwallseqavg[n_t-1];
		acceptances = 0;
		tries = 0;
		std::fill_n(rewallseqavg, n_t-1, 0);
		std::fill_n(imwallseqavg, n_t-1, 0);

		for (int j=1;j<=N_subseq;j++){
		//inside a single field config

			double sumplaq = 0;



			//----------update links--------------
			for(int i=0;i<n;i++) {
				acceptances += lattice[i].update(phases[intdistr(intgen)],uniformdistr(ugen));
				tries += 1;
			}

			//----------do operations-------------
			for(int i=0;i<n;i++) {
				sumplaq += lattice[i].getplaqsum();			//add to total sum the sum of plaqs surrounding this link
			}

			;
			std::pair<double, double> Tpair;
			std::pair<double, double> tpair;

			double xyplaqavgsum = 0;
			for (int t=0;t<n_t;t++){
				tpair = twallarray[t].getvalues();
				xyplaqavgsum += tpair.first;
			}
			xyplaqavgsum = xyplaqavgsum/n_t;

			for (int T=0;T<n_t;T++){
				Tpair = twallarray[T].getvalues();
				Tpair.first = Tpair.first - xyplaqavgsum;
				for(int t=0;t<n_t;t++){
					tpair = twallarray[(t+T)%n_t].getvalues();
					rewallseqavg[t] += (tpair.first-xyplaqavgsum) * Tpair.first;
					imwallseqavg[t] += tpair.second * Tpair.second;
				}
			}

			avgplaqsum += sumplaq/(N_plaq * 4);		//divide the sum of all plaqs in the lattice by the number of plaqs and inc the sequence avg

		}

		for(int i=0;i<n_t;i++){
			rewallseqavg[i] = rewallseqavg[i]/(N_subseq*n_t);
			imwallseqavg[i] = imwallseqavg[i]/(N_subseq*n_t);
		}

		std::cout<<"m_0++ seq"<<k<<":";
		std::cout<< std::endl;
		outfile<<"m_0++ seq"<<k<<":";
		outfile<< std::endl;
		for(int i=0;i<n_t;i++){
			std::cout << rewallseqavg[i]<<", ";
			outfile << rewallseqavg[i]<<", ";
		}
		std::cout<< std::endl;
		outfile<< std::endl;

		std::cout<<"m_0-- seq"<<k<<":";
		std::cout<< std::endl;
		outfile<<"m_0-- seq"<<k<<":";
		outfile<< std::endl;
		for(int i=0;i<n_t;i++){
			std::cout << imwallseqavg[i]<<", ";
			outfile << imwallseqavg[i]<<", ";
		}
		outfile<< std::endl;
		std::cout << std::endl;

		avgplaqarray[k] = avgplaqsum/N_subseq;
		std::cout<<"Plaqavg:" << avgplaqarray[k] << std::endl;
		std::cout << "Acceptances: "<<acceptances<<"/"<<tries<< std::endl;
		outfile<<"Plaqavg:" <<std::endl;
		outfile<< avgplaqarray[k] << std::endl;
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

   	outfile <<"avgplaq:"<<plaqavg<<std::endl;
   	outfile <<"plaqsd:"<<plaqsd<<std::endl;
   	outfile <<"completed in:"<< after2 - now2 << std::endl;
   	outfile.close();
  	}





