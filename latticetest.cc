#include <iostream>
#include <array>
#include <string>
#include "constants.h"
#include "indexing.h"
#include "linkclass.h"



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

//		int x,y,t;
//		x=1;
//		while (x != -100){
//			std::cout << "index(x y t):";
//			std::cin >> x >> y >> t;
//			twallarray[t].getplaqvals(x,y);
//
//		}
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


void latticetest()
{
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
  	std::string in = "";
  	int mu,x,y,t;
  	while (in != "halt"){
  		std::cout << "Command(link,plaq):";
  		std::cin >> in;
  		if (in == "link"){
  			std::cout << "index(mu x y t):";
  			std::cin >> mu >> x >> y >> t;
  			std::array<int, 4> d = {mu,x,y,t};
  			std::cout<<lattice[getindex(d)].getvalue()<<std::endl;
  			} else{ if (in == "plaq"){
  				std::cout << "index(mu x y t):";
  				std::cin >> mu >> x >> y >> t;
  				std::array<int, 4> d = {mu,x,y,t};
  				lattice[getindex(d)].getstaples();
  					}
  				else{ if (in=="loop") {
  					for (int j=0;j<100000;j++){
  					for (int i=0;i<n;i++){
  					lattice[i].getstaplessilent();
  					}
  						}
  				}

  					}
  			}
  		}

  	}


