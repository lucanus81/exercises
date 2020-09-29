#include <iostream>
#include <queue>
#include <vector>
#include <memory>
#include <utility>
#include <algorithm>

struct data {
	char c;
	unsigned int freq;
};

struct huffman_node {
	std::unique_ptr<huffman_node> left;
	std::unique_ptr<huffman_node> right;
	unsigned int freq;
	char data;
	unsigned char bit{};

	huffman_node(std::unique_ptr<huffman_node>&& a, std::unique_ptr<huffman_node>&& b, unsigned int f, char d) :
		left{std::move(a)}, right{std::move(b)}, freq{f}, data{d} {}
};

struct compare {
	bool operator()(const std::unique_ptr<huffman_node>& a, const std::unique_ptr<huffman_node>& b) const { return a->freq > b->freq; } 
};

std::unique_ptr<huffman_node> extract_min(std::vector<std::unique_ptr<huffman_node>>& v) {
	std::pop_heap(v.begin(), v.end(), compare{});
	std::unique_ptr<huffman_node> min{std::move(v.back())};
	v.pop_back();
	return min;	
}

std::unique_ptr<huffman_node>
make_huffman_code(const std::vector<data>& v) {

	std::vector<std::unique_ptr<huffman_node>> queue;
	queue.reserve(v.size());
	for (const data& d : v)
		queue.push_back(std::make_unique<huffman_node>(nullptr, nullptr, d.freq, d.c));
	std::make_heap(queue.begin(), queue.end(), compare{});

	unsigned int end=v.size() - 1;
	for (unsigned int i=0; i<end; ++i) {
		std::unique_ptr<huffman_node> z=std::make_unique<huffman_node>(nullptr, nullptr, 0, 0);
		std::unique_ptr<huffman_node> x{extract_min(queue)};
		std::unique_ptr<huffman_node> y{extract_min(queue)};
		z->freq=x->freq+y->freq;
		x->bit='0';
		y->bit='1';
		z->left=std::move(x);
		z->right=std::move(y);

		queue.push_back(std::move(z));
		std::push_heap(queue.begin(), queue.end(), compare{});
	}
	
	return extract_min(queue);
}

void pre_order(const std::unique_ptr<huffman_node>& r,  unsigned int spaces) {
	if (r != nullptr) {
		pre_order(r->left, spaces + 2);
		for (unsigned int i=0; i<spaces; ++i) std::cout <<' ';
		std::cout <<r->freq <<':' <<r->data <<':' <<r->bit <<'\n';
		pre_order(r->right, spaces + 2);
	}
}

void all_codes(const std::unique_ptr<huffman_node>& r, std::vector<char>& code) {
	if (r != nullptr) {
		code.push_back(r->bit);
		if (r->left == nullptr && r->right == nullptr) {
			std::cout <<r->data <<':';
			for (auto b : code) std::cout <<b;
			std::cout <<'\n';
		} 
		
		all_codes(r->left, code);
		all_codes(r->right, code);
		code.pop_back();	
	}
}

int main() {
	std::vector<data> v{{'a',45}, {'b',13}, {'c',12}, {'d',16}, {'e',9}, {'f',5}};
	std::unique_ptr<huffman_node> root=make_huffman_code(v);
	pre_order(root, 0);
	
	std::cout <<"How to encode out input string:\n"; 
	std::vector<char> codes;
	all_codes(root, codes);

	return 0;
}
