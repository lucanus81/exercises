#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <functional>

std::vector<std::string> split(const std::string& input, unsigned int width) {
	unsigned int q=input.size()/width;
	unsigned int r=input.size()%width;

	std::vector<std::string> res;
	res.reserve(r == 0 ? q : q+1);

	for (size_t s=0; s<q; ++s)
		res.push_back(input.substr(s*width, width));

	if (r != 0)
		res.push_back(input.substr(q*width, r));

	return res;
}

struct node {
	char data;
	node* left, *right;
};

std::string all_sub_trees(node* n, std::unordered_map<std::string, unsigned int>& h) {
	if (n == nullptr)
		return "";

	std::string r{"{"};
	r += all_sub_trees(n->left, h);
	r += n->data;
	r += all_sub_trees(n->right, h);
	r += "}";
	
	++h[r];
	return r; 
}

void grep_context(const std::vector<std::string>& lines, 
								  std::function<bool(std::string const&)> pred, 
									unsigned int context) {
	std::size_t k=0;
	for (size_t i=0; i<lines.size(); ) {
		if (pred(lines[i])) {
			for (ptrdiff_t j=std::max(i-context,k); j >= 0 && j <= i+context; ++j)
				std::cout <<lines[j] <<'\n';
			i += context;
			k=i+1;
		} else
			++i;
	}
}

int main() {
	std::string text{"12345678901234567"};
	std::cout <<text <<'\n';
	for (auto const& s : split(text, 5))
		std::cout <<s <<'\n';

	node r4_2{'4', nullptr, nullptr};
	node r4_3{'4', nullptr, nullptr};
	node r2_1{'2', &r4_3, nullptr};
	node r3{'3', &r2_1, &r4_2};
	node r4_1{'4', nullptr, nullptr};
	node r2{'2', &r4_1, nullptr};
	node r{'1', &r2, &r3};

	std::unordered_map<std::string, unsigned int> h;
	all_sub_trees(&r, h);
	for (auto const& p : h)
		std::cout <<p.first <<':' <<p.second <<'\n';

	std::vector<std::string> t{"apple", "cake", "bat", "bomb", "cat", "boredom", "dog", "dear"};
	grep_context(t, [](std::string const& i) { return i.size() >= 2 && i[0] == 'b' && i[1] == 'o'; }, 1);
	return 0;
}
