#include <iostream>
#include <array>
#include <string>
const int n_dir = 3;
const int n_x = 10;
const int n_y = 20;
const int n_t = 10;
const int n = n_dir * n_x * n_y * n_t;

int getindex(std::array<int, 4> _index) {		//check the array passing syntax inc zero or 1 based indexing
	int i = n/3 * _index[0] + ( (_index[1] % n_x) + n_x * ((_index[2] % n_y) + n_y * (_index[3] % n_t))); //check remainder div
	return i;
}

class staple {			//staples belong to links to is no notion of an array of staples
	private:
		double *_links[3];		//init array of pointers, remember to dereference when you want the variable
		int dir;
	
	public:
		staple(int x, double _lattice[n] = NULL, int _index[4] = NULL, int lambda = 100): dir(x) {		//index passed by value
					if (dir == 0){
						for (int i=0; i<=3; i++) {
							_links[i] = NULL;
						}
					}
		}

		void initstaple(int x, double _lattice[n],std::array<int, 4> _index, int lambda = 100) {		//index passed by value
				dir = x;
				int mu = _index[0];
				if (dir == 1) {
					_index[0] = lambda;
					_links[2] = &_lattice[getindex(_index)];	//set pointer to point to appropriate link
					_index[mu+1] += 1;		//increment the mu-dir coordinate by one
					_links[0] = &_lattice[getindex(_index)];
					_index[0] = mu;
					_index[mu+1] -= 1;
					_index[lambda+1] += 1;
					_links[1] = &_lattice[getindex(_index)];
				} else { if (dir == -1) {
					_index[lambda+1] -= 1;
					_links[1] = &_lattice[getindex(_index)];
					_index[0] = lambda;
					_links[2] = &_lattice[getindex(_index)];
					_index[mu+1] += 1;
					_links[0] = &_lattice[getindex(_index)];
						}
					}
		}

	double **getvalues(){		//double derefernce, pointer to array of pointers
		return _links;
	}
	double getvalue() {
		if (dir == 1) {
			return *_links[0] - *_links[0] - *_links[2];	//deref each of the three pointers to get staple
		} else {return *_links[2] - *_links[0] - *_links[2]; }
	}

};


class link {
private:
	double *_value;		//pointer to link value
	staple _staples[4];	//array of staple pointers, check syntax, check how james parses
	

public:
	link(): _staples{0,0,0,0}, _value(NULL) {}

	void initlink(double _lattice[n], std::array<int, 4> _index) {		//lattice is a single pointer, _index = {mu, x, y, z}
		_value = &_lattice[getindex(_index)];     //value contains the addr of the value
	}

	double getvalue() {
			return *_value;
	}

	void getstaples() {
		for (int i=0;i<4;i++){
		  	double** stplarray;
		  	stplarray = _staples[i].getvalues();
		  	for (int j=0;j<3;j++){
		  		std::cout<<*stplarray[j]<<" ";
		  		}
		  		std::cout<<std::endl;
		  	};
		}
	void getstaplessilent() {
		for (int i=0;i<4;i++){
		  	double** stplarray;
		  	stplarray = _staples[i].getvalues();
		  	for (int j=0;j<3;j++){
		  		if (*stplarray[j] == -1){
		  			std::cout<<"oh dear!";
		  		}
		  		}
		  	};
		}
	void setvalue(double val) {
		*_value = val;
	}

	void getaction(double val) {
		;
	}

	void update(double val) {
			;
		}
	void setstaples(double _lattice[n],std::array<int, 4> _index) {
		for(int loopi=0, staplesi=0; loopi<=2; loopi++) {
			if (_index[0] != loopi) {
				_staples[staplesi++].initstaple(1, _lattice, _index, loopi);
				_staples[staplesi++].initstaple(-1, _lattice, _index, loopi); //opposite dir
			}
		}
	}
};



int main()
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


