#include <bitset>
#include <iostream>

// You are given two 32-bit numbers, N and M, and two bit positions, i and j.
// Write a method to set all bits between i and j in N equal to M (e g , M 
// becomes a substring of N located at i and starting at j)
//
// EXAMPLE:
// Input: N = 10000000000, M = 10101, i = 2, j = 6
// Output: N = 10001010100
unsigned int multi_set(unsigned int N, unsigned int M, unsigned int i, unsigned int j) {
	static const unsigned int max_allowed_index = sizeof(N) * 8;
	if (i > j || i >= max_allowed_index || j >= max_allowed_index)
		return N;
	
	unsigned int mask = ~0;
	mask >>= (max_allowed_index - j + 1);
	M &= mask;

	return N |= (M << i);
}

int count_bits(unsigned int N) {
	unsigned int count=0;
	while (N) {
		count += (N & 1);
		N >>= 1;
	}
	
	return count;
}

int count_bits2(unsigned int N) {
	unsigned int count=0;
	while (N) {
		N &= (N-1);
		++count;
	}

	return count;
}

int count_bits3(unsigned int N) {
	static unsigned int map[]{
		0, 1, 1, 2, 1, 2, 2, 3, 
    1, 2, 2, 3, 2, 3, 3, 4};

	unsigned int count=0;
	for (unsigned int i=0; i<sizeof(N)*8/4; ++i) {
		unsigned int nibble = (N >> (i*4)) & 0xF;
		count += map[nibble];
	}

	return count;
}

void next_previous(unsigned int N) {
	
	unsigned int count=count_bits(N);
	
	unsigned int next = N+1;
	while (count_bits(next) != count) ++next;
	unsigned int prev = N-1;
	while (count_bits(prev) != count) --prev;
	
	std::cout <<std::bitset<32>(N) <<'\n'
		<<std::bitset<32>(prev) <<'\n'
		<<std::bitset<32>(next) <<'\n';
}

// Write a function to determine the number of bits required 
// to convert integer A to integer B
unsigned int change_to(unsigned int N, unsigned int M) {
	return count_bits(N ^ M);
}

int main() {
//	std::bitset<32> N{"10000000000"}, M{"11111"};
//	std::cout <<std::bitset<32>(multi_set(N.to_ulong(), M.to_ulong(), 2, 6)) <<'\n';
	
//	next_previous(24);
//	std::cout <<std::bitset<32>(143) <<'\n' <<std::bitset<32>(17) <<'\n' <<change_to(143,17) <<'\n';
	for (unsigned int i=0; i<0xFFFF; ++i)
		if (count_bits(i) != count_bits3(i))
			std::cout <<"Error for " <<i <<'\n';
	//std::cout <<count_bits3(17) <<' ' <<std::bitset<32>(17) <<'\n';	
return 0;
}
