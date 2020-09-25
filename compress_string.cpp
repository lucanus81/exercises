#include <iostream>
#include <vector>
#include <cassert>

struct solution {
	
	void overwrite_data(std::vector<char>& s, std::size_t& overwrite_start, char c, std::size_t count) {
		std::size_t q=count/9, r=count%9;
		for (std::size_t w=0; w<q; ++w) {
			s[overwrite_start++] = c;
			s[overwrite_start++] = '9';
		}
			
		s[overwrite_start++] = c;
		if (r > 1)
			s[overwrite_start++] = '0' + r;
	}
	
	std::size_t compress(std::vector<char>& s) {
		std::size_t i = 0;
		std::size_t end = s.size();
		std::size_t overwrite_start = 0;

		while (i < end) {
			std::size_t j = i + 1;
			std::size_t count = 1;
			while (j < end && s[i] == s[j]) { 
				++count;
				++j;
			}
			
			overwrite_data(s, overwrite_start, s[i], count);			
			i = j; 
		}
		
		s.erase(s.begin()+overwrite_start, s.end());

		return overwrite_start;
	}
};

int main() {
	std::vector<char> v1; 
	std::size_t i1=solution{}.compress(v1);
	assert(i1==0 && v1.size() == 0);
	
	{
	std::vector<char> v{'a','a','b'};
	std::size_t i=solution{}.compress(v);
	assert(i==3 && v.size() == 3);
	std::vector<char> v_expected{'a','2','b'};
	assert(v == v_expected);
	}

	{
	std::vector<char> v{'a','a','a','a','a','a','a','a','a','a','a','a','b'};
	std::size_t i=solution{}.compress(v);
	assert(i==5 && v.size() == 5);
	std::vector<char> v_expected{'a','9','a','3','b'};
	assert(v == v_expected);
	}

	return 0;
}
