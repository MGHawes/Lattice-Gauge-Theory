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
#include "wilsonwall.h"

  	double latticedata[n];
  	link lattice[n];
  	twall twallarray[n_t];
  	wilsonwall wwallarray[n_t];

int main(int argc, char* argv[]){

	std::stringstream ss;
	std::string runNo;
	ss << argv[1];
	ss >> runNo;

	std::string fname;
	std::stringstream fnamestream;
	std::ofstream outfile;

	fnamestream << "lgt"<< n_x << n_y << n_t << N_equilib << N_subseq << beta << "x"<< runNo <<".txt";
	fname = fnamestream.str();

	outfile.open(fname);

	std::time_t starttime = time(0);

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
		wwallarray[t].initwwall(latticedata,t);
	}



    //initialise gaussian phases set
    //std::random_device gauss_dev;
    std::mt19937 gaussgen(std::time(0));
    std::normal_distribution<double> gaussian(mean,var);

    double phases[2*N_v+1];		//pairs plus the identity
	phases[0] = 0;				//identity
    for (int i=0, j=1;i<N_v;i++){		
    	double g = gaussian(gaussgen);
    	phases[j++] = g;
    	phases[j++] = -g;
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

    std::time_t equilibnow = time(0);
    std::time_t equilibafter = time(0);
    for (int j=1;j<=N_equilib;j++){
		for(int i=0;i<n;i++) {
			acceptances += lattice[i].update(phases[intdistr(intgen)],uniformdistr(ugen));
			tries += 1;
		}
		if (j % N_updatesperstatus == 0){
			std::cout<<j<<std::endl;
			equilibafter = time(0);
			double eta = double(equilibafter - equilibnow)*(N_subseq*N_seq + (N_equilib - j))/double(N_updatesperstatus*60);
			equilibnow = time(0);
			std::cout << "eta: "<< eta << " mins" <<std::endl;
			std::cout << "Acceptances: "<<acceptances<<"/"<<tries<< std::endl;
			acceptances = 0;
			tries = 0;
		}
    }

    std::time_t endequilib = time(0);

    std::cout <<"Equilibriated:"<< endequilib - starttime << std::endl;
    outfile <<"Equilibriated:"<< endequilib - starttime << std::endl;
    double eta = (endequilib - starttime)*(N_subseq*N_seq)/(N_equilib*60);
    std::cout <<"eta: "<< eta << " mins" <<std::endl;

    std::time_t startsims = time(0);


    double avgplaqarray[N_seq];
//    double avgrewall[N_seq][n_t-1];			//store each t array in a particular sequence row
//    double avgimwall[N_seq][n_t-1];
    equilibnow = time(0);
	for (int seq_no=0;seq_no<N_seq;seq_no++){
		//inside a single sequence of field configs
		double avgplaqsum = 0;
		double rewallseqavg[n_t];
		double imwallseqavg[n_t];
		double wwallseqavg[n_t];
		acceptances = 0;
		tries = 0;
		std::fill_n(rewallseqavg, n_t, 0);
		std::fill_n(imwallseqavg, n_t, 0);
		std::fill_n(wwallseqavg, n_t, 0);

		for (int config_no=1;config_no<=N_subseq;config_no++){
		//inside a single field config

			double sumplaq = 0;



			//----------update links--------------
			for(int site=0;site<n;site++) {
				acceptances += lattice[site].update(phases[intdistr(intgen)],uniformdistr(ugen));
				tries += 1;
			}

			//----------do operations-------------
			for(int site=0;site<n;site++) {
				sumplaq += lattice[site].getplaqsum();			//add to total sum the sum of plaqs surrounding this link
			}

			;
			std::pair<double, double> Tpair;
			std::pair<double, double> tpair;
			std::pair<double, double> Wpair;
			std::pair<double, double> wpair;

			double xyplaqavgsum = 0;
			for (int t=0;t<n_t;t++){
				tpair = twallarray[t].getvalues();
				xyplaqavgsum += tpair.first;
			}
			xyplaqavgsum = xyplaqavgsum/n_t;

			for (int T=0;T<n_t;T++){
				Wpair = wwallarray[T].getvalues();
				Tpair = twallarray[T].getvalues();
				Tpair.first = Tpair.first - xyplaqavgsum;
				for(int t=0;t<n_t;t++){
					tpair = twallarray[(t+T)%n_t].getvalues();
					wpair = wwallarray[(t+T)%n_t].getvalues();
					rewallseqavg[t] += (tpair.first-xyplaqavgsum) * Tpair.first;
					imwallseqavg[t] += tpair.second * Tpair.second;
					wwallseqavg[t] += wpair.first * Wpair.first + wpair.second * Wpair.second;
				}
			}

			avgplaqsum += sumplaq/(N_plaq * 4);		//divide the sum of all plaqs in the lattice by the number of plaqs and inc the sequence avg

		}

		for(int i=0;i<n_t;i++){
			rewallseqavg[i] = rewallseqavg[i]/(N_subseq*n_t);
			imwallseqavg[i] = imwallseqavg[i]/(N_subseq*n_t);
			wwallseqavg[i] = wwallseqavg[i]/(N_subseq*n_t);
		}

		std::cout<<"m_0++ seq"<<seq_no<<":";
		std::cout<< std::endl;
		outfile<<"m_0++ seq"<<seq_no<<":";
		outfile<< std::endl;
		for(int i=0;i<n_t;i++){
			std::cout << rewallseqavg[i]<<", ";
			outfile << rewallseqavg[i]<<", ";
		}
		std::cout<< std::endl;
		outfile<< std::endl;

		std::cout<<"m_0-- seq"<<seq_no<<":";
		std::cout<< std::endl;
		outfile<<"m_0-- seq"<<seq_no<<":";
		outfile<< std::endl;
		for(int i=0;i<n_t;i++){
			std::cout << imwallseqavg[i]<<", ";
			outfile << imwallseqavg[i]<<", ";
		}
		outfile<< std::endl;
		std::cout << std::endl;

		std::cout<<"wilson seq"<<seq_no<<":";
		std::cout<< std::endl;
		outfile<<"wilson seq"<<seq_no<<":";
		outfile<< std::endl;
		for(int i=0;i<n_t;i++){
			std::cout << wwallseqavg[i]<<", ";
			outfile << wwallseqavg[i]<<", ";
		}
		outfile<< std::endl;
		std::cout << std::endl;

		avgplaqarray[seq_no] = avgplaqsum/N_subseq;
		std::cout<<"Plaqavg:" << avgplaqarray[seq_no] << std::endl;
		std::cout << "Acceptances: "<<acceptances<<"/"<<tries<< std::endl;
		outfile<<"Plaqavg:" <<std::endl;
		outfile<< avgplaqarray[seq_no] << std::endl;

		equilibafter = time(0);
		double eta = double(equilibafter - equilibnow)*(N_seq-seq_no-1)/double(60);
		equilibnow = time(0);
		std::cout << "eta: "<< eta << " mins" <<std::endl;
	}

	double plaqavg = 0;
	double plaqsquaremean = 0;
	for (int l=0;l<N_seq;l++){
		plaqavg += avgplaqarray[l];
		plaqsquaremean += avgplaqarray[l]*avgplaqarray[l];
	}
	plaqsquaremean = plaqsquaremean/N_seq;
	plaqavg = plaqavg/N_seq;
	double plaqsd = std::sqrt(plaqsquaremean - plaqavg*plaqavg);

	std::time_t after2 = time(0);
    std::cout <<"avgplaq:"<<plaqavg<<std::endl;
    std::cout <<"plaqsd:"<<plaqsd<<std::endl;
    std::cout <<"completed in:"<< after2 - startsims << std::endl;

   	outfile <<"avgplaq:"<<plaqavg<<std::endl;
   	outfile <<"plaqsd:"<<plaqsd<<std::endl;
   	outfile <<"completed in:"<< after2 - startsims << std::endl;
   	outfile.close();
  	}





