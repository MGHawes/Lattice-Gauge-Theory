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

//int main()
//{
//  	double latticedata[n];
//
//
//  	link lattice[n];
//
// 	for (int i=0; i<n; i++){
//  		latticedata[i] = i;
//  	}
// 	std::array<int, 4> index;
//  	for(int mu=0; mu<=2; mu++) {
//  		index[0] = mu;
//  		for (int x=0; x<n_x; x++) {
//  			index[1]=x;
//  			for (int y=0; y<n_y; y++) {
//  				index[2]=y;
//  				for (int t=0; t<n_t; t++) {
//  					index[3]=t;
//  					lattice[getindex(index)].initlink(latticedata,index);
//  				}
//  			}
//  		}
//  	}
//  	for(int mu=0; mu<=2; mu++) {
//  	  		index[0] = mu;
//  	  		for (int x=0; x<n_x; x++) {
//  	  			index[1]=x;
//  	  			for (int y=0; y<n_y; y++) {
//  	  				index[2]=y;
//  	  				for (int t=0; t<n_t; t++) {
//  	  					index[3]=t;
//  	  					lattice[getindex(index)].setstaples(latticedata,index);
//  	  				}
//  	  			}
//  	  		}
//  	}
//  	std::string in = "";
//  	int mu,x,y,t;
//  	while (in != "halt"){
//  		std::cout << "Command(link,plaq):";
//  		std::cin >> in;
//  		if (in == "link"){
//  			std::cout << "index(mu x y t):";
//  			std::cin >> mu >> x >> y >> t;
//  			std::array<int, 4> d = {mu,x,y,t};
//  			std::cout<<lattice[getindex(d)].getvalue()<<std::endl;
//  			} else{ if (in == "plaq"){
//  				std::cout << "index(mu x y t):";
//  				std::cin >> mu >> x >> y >> t;
//  				std::array<int, 4> d = {mu,x,y,t};
//  				lattice[getindex(d)].getstaples();
//  					}
//  				else{ if (in=="loop") {
//  					for (int j=0;j<100000;j++){
//  					for (int i=0;i<n;i++){
//  					lattice[i].getstaplessilent();
//  					}
//  						}
//  				}
//
//  					}
//  			}
//  		}
//
//  	}

int main(){
  	double latticedata[n];


  	link lattice[n];

 	for (int i=0; i<n; i++){
  		latticedata[i] = i;
  	}
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
    //initialise gaussian phases set
    std::random_device gauss_dev;
    std::mt19937 gaussgen(gauss_dev());
    std::normal_distribution<double> gaussian(mean,var);

    double phases[2*N_v+1];		//pairs plus the identity
	phases[0] = 0;				//identity
    for (int i=0, j=1;i<N_v;i++){		//iter through N_v times
    	double g = gaussian(gaussgen);
    	phases[j++] = g;				//add the two pairs of phases
    	phases[j++] = -g;				//add the two pairs of phases
    }


  	//declare the rand uniform generators for the metropolis algorithm
    std::random_device rand_dev;
    std::mt19937 ugen(rand_dev());
    std::uniform_real_distribution<double> uniformdistr(0, 1);

    std::random_device int_dev;
    std::mt19937 intgen(int_dev());
    std::uniform_int_distribution<int> intdistr(0,N_v);

    for (int j=1;j<=N_equilib;j++){
		for(int i=0;i<n;i++) {
			lattice[i].update(phases[intdistr(intgen)],uniformdistr(ugen));
		}
    }
    std::cout <<"equilibriated";
    double avgplaqsum = 0;
    for (int j=1;j<=N_subseq;j++){
    		//inside a single field config
    		for(int i=0;i<n;i++) {
    			lattice[i].update(phases[intdistr(intgen)],uniformdistr(ugen));
    		}
    		double sumplaq = 0;
    		for(int i=0;i<n;i++) {
    		    sumplaq += lattice[i].getplaqsum();			//add to total sum the sum of plaqs surrounding this link
    		  //  std::cout << i << ":" << sumplaq << std::endl;
    		}
    		std::cout << j << ":" << sumplaq/(N_plaq * 4) << std::endl;
    		avgplaqsum += sumplaq/(N_plaq * 4);		//divide the sum of all plaqs in the lattice by the number of plaqs and inc the sequence avg

        }
    double avgplaq = avgplaqsum/N_subseq;
    std::cout <<avgplaq;
  	}





