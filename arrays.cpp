#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <unordered_set>

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

struct heap_indexer {
	static size_t left(size_t parent) { return 2*parent + 1; } 
	static size_t right(size_t parent) { return 2*parent + 2; } 
};

std::vector<int> max_k_elements2(const std::vector<int>& heap, unsigned int k) {
	std::vector<int> res;
	size_t N=heap.size() >= k ? k : heap.size();
	res.reserve(N);

	res.push_back(heap[0]);
	std::unordered_set<size_t> c{heap_indexer::left(0), heap_indexer::right(0)};
	for (size_t i=0; i<N-1; ++i) {
		auto pos_max=std::max_element(c.begin(), c.end(), 
			[&heap](size_t l, size_t r) { return heap[l] < heap[r]; });
		res.push_back(heap[*pos_max]);
		
		size_t new_left = heap_indexer::left(*pos_max);
		size_t new_right = heap_indexer::right(*pos_max);
		c.erase(pos_max);
		if (new_left < heap.size())
			c.insert(new_left);
		if (new_right < heap.size())
			c.insert(new_right);
	}

	return res;
}

void test_max_k_elements() {
	std::vector<int> v{90,89,70,36,75,63,65,21,18,15};

	std::vector<int> res{ max_k_elements2(v,5) };
	std::vector<int> expected{ max_k_elements(v,5) };
	assert(res == expected);
}

// -----------------------------------------------------------------
// Transform an array into an heap
void heapify(std::vector<int>& v, size_t i) {
	size_t largest{i}, left{2*i+1}, right{2*i+2};
	if (left < v.size() && v[largest] < v[left])
		largest=left;
	if (right < v.size() && v[largest] < v[right])
		largest=right;

	if (largest != i) {
		std::swap(v[i], v[largest]);
		heapify(v, largest);
	}
}

void make_heap(std::vector<int>& v) {
	size_t start_index{(v.size()/2) -1};
	for (size_t i=0; i<=start_index; ++i)
		heapify(v, start_index-i);
	//for (int i=start_index; i>=0; --i)
	//	heapify(v, i);
}

std::vector<int> partial_multiply(const std::vector<int>& v) {
	std::vector<int> prefix(v.size(), 1);
	std::vector<int> suffix(v.size(), 1);
	
	for (size_t i=1; i<v.size(); ++i)
		prefix[i]=v[i-1]*prefix[i-1];
	for (std::size_t j=0, last=v.size()-2; j<=last; ++j)
		suffix[last-j]=v[last-j+1]*suffix[last-j+1];
	
	std::vector<int> res(v.size(), 1);
	for (size_t i=0; i<v.size(); ++i)
		res[i]=prefix[i]*suffix[i];
	return res;
}

int main() {
	test_binary_search();
	test_max_k_elements();
	
	std::vector<int> v{1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17};
	make_heap(v);
	
	std::vector<int> w{v};
	std::make_heap(w.begin(), w.end());
	if (v != w)
		std::cout <<"error";
	
	std::vector<int> r{ partial_multiply({1, 2}) };
	for (int i : r)
		std::cout <<i <<' ';
	std::cout <<'\n';

	return 0;
}
