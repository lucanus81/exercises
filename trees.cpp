#include <iostream>
#include <utility>
#include <cmath>
#include <cassert>
#include <array>
#include <forward_list>
#include <unordered_map>

template <typename T>
struct node {
	T data;
	node* left;
	node* right;
};

namespace traversal {

template<typename T, typename Functor>
void tree_preorder_walk(const node<T>* curr, Functor f) {
	if (curr != nullptr) {
		f(curr);
		tree_preorder_walk(curr->left, f);
		tree_preorder_walk(curr->right, f);
	}
} 

template<typename T, typename Functor>
void tree_inorder_walk(const node<T>* curr, Functor f) {
	if (curr != nullptr) {
		tree_inorder_walk(curr->left, f);
		f(curr);
		tree_inorder_walk(curr->right, f);
	}
}

} // namespace traversal

template <typename T>
void tree_print_by_level(const node<T>* node, int indent) {
	if  (node != nullptr) {
		for (int i=0; i<indent; ++i) std::cout <<'_';
		std::cout <<node->data <<'\n';
		tree_print_by_level(node->left, indent+1);
		tree_print_by_level(node->right, indent+1);
	}
}
 
template <typename T>
void tree_insert(node<T>* &root, T value) {
	if (root == nullptr) {
		root = new node<T>{std::forward<T>(value), nullptr, nullptr};
	} else
		if (root->data < value)
			tree_insert(root->right, value);
		else
			tree_insert(root->left, value);
}

template <typename T>
node<T>* tree_batch_insert(std::initializer_list<T> values) {
	node<T>* root = nullptr;
	for (const auto i : values)
		tree_insert(root, i);

	return root;		
}

template <typename T, typename Functor>
int tree_height(node<T>* root, Functor f) {
	if (root == nullptr)
		return 0;
	else {
		int left=tree_height(root->left, f);
		int right=tree_height(root->right, f);
		return 1 + f(left, right);
	}
}

template <typename T>
bool tree_is_balanced(node<T>* n) {
	int min=tree_height(n, [](int left, int right) { return std::min(left, right); });
	int max=tree_height(n, [](int left, int right) { return std::max(left, right); });
	return (max-min) <= 1;
}

// --------------------------------------------
// Given a sorted array, write an algorithm to create a tree with
// minimal height
template <typename T>
void traverse_array_recursive(const T* a, int left, int right, node<T>* &root) {
	if (left > right)
		return;

	int middle = (left+right)/2;
	tree_insert(root, a[middle]);
	traverse_array_recursive(a, left, middle -1, root);
	traverse_array_recursive(a, middle + 1, right, root);
}

template <typename T, std::size_t N>
node<T>* traverse_array(const std::array<T,N> a) {
	node<T>* root{nullptr};
	traverse_array_recursive(a.cbegin(), 0, a.size() - 1, root);

	return root;
}

// --------------------------------------------
// Given a binary search tree, design an algorithm which creates 
// a linked list of all the nodes at each depth (i e , if you have 
// a tree with depth D, you’ll have D linked lists)
template <typename T>
void tree_to_list_by_level(node<T>* root, int level, std::unordered_map<int, std::forward_list<T>>& m) {
	if (root == nullptr)
		return;
	
	tree_to_list_by_level(root->left, level + 1, m);
	if (auto it=m.find(level); it != m.end())
		it->second.push_front(root->data);
	else
		m.insert(std::make_pair(level, std::forward_list{root->data}));
		
	tree_to_list_by_level(root->right, level + 1, m);
}

int main() {
	node<int>* r = tree_batch_insert({10,5,123,7,8});
	tree_print_by_level(r,0);
	
	auto printer = [](const node<int>* n) { std::cout <<n->data <<' '; };
	traversal::tree_preorder_walk(r, printer);
	std::cout <<'\n';
	traversal::tree_inorder_walk(r, printer);
	std::cout <<'\n';
	
	assert(tree_height(r, [](int i, int j){ return std::min(i,j);}) == 2);
	assert(tree_height(r, [](int i, int j){ return std::max(i,j);}) == 4);
	assert(tree_is_balanced(r) == false);

	assert(tree_is_balanced(tree_batch_insert({1,2,-1})));
	assert(tree_is_balanced(tree_batch_insert({1,2})));
	assert(tree_is_balanced(tree_batch_insert({10,5,123,7,800})));
	assert(tree_is_balanced(tree_batch_insert({1,2,3,4})) == false);

	tree_print_by_level(traverse_array(std::array{1,2,3,4,5}), 0);

	std::unordered_map<int, std::forward_list<int>> result;
	tree_to_list_by_level(tree_batch_insert({10,5,123,7,8}), 0, result);
	for (const auto& i : result) {
		std::cout <<i.first <<':';
		for (const auto& j : i.second)
			std::cout <<j <<' ';
		std::cout <<'\n';
	}
	
	return 0;
}
