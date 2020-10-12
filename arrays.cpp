#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>

int binary_search(int A[], int key, unsigned int start, unsigned int end) {
	if (end >= start) {		
		unsigned int middle=(start+end)/2;
		if (A[middle] == key)
			return middle;
		else 
			if (key < A[middle])
				return binary_search(A, key, start, middle-1);
			else
				return binary_search(A, key, middle+1, end);
	} else
		return -1;	 
}

void test_binary_search() {
	int A[]{1,2,3,4,5,6,7,8,9,10};
	unsigned int N{sizeof(A)/sizeof(*A) - 1};
	
	for (unsigned int i=0; i<=N; ++i)
		assert(i == binary_search(A, A[i], 0, N));
	assert(-1 == binary_search(A, 999, 0, N));
}

// -------------------------------------------------------------------
std::vector<int> max_k_elements(const std::vector<int>& heap, unsigned int k) {
	std::vector<int> copy{heap};
	std::vector<int> result;
	result.reserve(k);

	for (unsigned int i=0; i<k; ++i) {
		std::pop_heap(copy.begin(), copy.end());
		result.push_back(copy.back());
		copy.pop_back();
	}

	return result;
}

void test_max_k_elements() {
	std::vector<int> v{90,89,70,36,75,63,65,21,18,15};

	std::vector<int> res{ max_k_elements(v,3) };
	std::vector expected{90,89,75};
	assert(res == expected);
}

int main() {
	test_binary_search();
	test_max_k_elements();

	return 0;
}
