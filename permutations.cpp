#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <algorithm>

void all_perm(std::string s, unsigned int l, unsigned int r) {
	if (l == r)
		std::cout <<s <<'\n'; 
	else 
		for (unsigned int i=l; i<=r; ++i) {
			std::swap(s[l], s[i]);
			all_perm(s, l+1, r);
			std::swap(s[l], s[i]);
		}
}

void all_pair_par(char* s, unsigned int left, unsigned int right, unsigned int pos) {
	if (left == 0 && right == 0)
		std::cout <<s <<'\n';
	else {
		if (left > 0) {
			s[pos]='[';
			all_pair_par(s, left - 1, right, pos + 1);
		}
		if (right > left) {
			s[pos]=']';
			all_pair_par(s, left, right - 1, pos + 1);
		}
	}
}


struct board {
	std::unique_ptr<char[]> place;
	unsigned int size{};
	
	board(unsigned int N) {
		size=N;
		place=std::make_unique<char[]>(N*N);
		std::fill(place.get(), place.get()+(N*N), '.');
	}

	void place_queen(unsigned int x, unsigned int y) {
		place[x * size + y] = 'X';	
	}

	void queens(unsigned int row, ) {
		if (row != size) {
			
		}
	}

	char element_at(unsigned int x, unsigned int y) const {
		return place[x * size + y];
	}
	
	
	static std::ostream& header(std::ostream& o, unsigned int length) {
		o <<' ' <<'+';		
		for (unsigned int i=0; i<length; ++i)
			o <<'-';
		o <<"+\n";

		return o;
	}

	friend std::ostream& operator<<(std::ostream& o, const board& b) {
		
		o <<"  ";		
		for (unsigned int i=0; i<b.size; ++i)
			o <<(i%10);
		o<<'\n';		
		header(o, b.size);
		for (unsigned int i=0; i<b.size; ++i) {
			o <<(i%10) <<'|';
			for (unsigned int j=0; j<b.size; ++j)
				o <<b.element_at(i, j);
			o <<"|\n";
		}

		header(o, b.size);
		return o;
	}
}; 

int main() {
	//std::string s{"0123456789"};
	//all_perm(s, 0, s.size() - 1);
	//const unsigned int N=3;
	//char s[N*2+1]={};
	//all_pair_par(s, N, N, 0);
	board b{8};
	std::cout <<b <<'\n';

	return 0;
}
