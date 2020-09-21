#include <iostream>
#include <stack>
#include <cassert>

bool is_open_bracket(char c) {
	return c == '{' || c == '[' || c == '(';
}

bool is_close_bracket(char c) {
	return c == '}' || c == ']' || c == ')';
}

bool matching_bracket(char saved, char curr) {
	return (curr == '}' && saved == '{') ||
		(curr == ']' && saved == '[') ||
		(curr == ')' && saved == '(');
}

bool check(const char* line) {
	if (line == nullptr)
		return false;
	
	std::stack<char> stack;
	for (const char* curr=line; *curr != '\0'; ++curr) {
		if (is_open_bracket(*curr))
			stack.push(*curr);
		else
			if (is_close_bracket(*curr)) {
				if (!stack.empty() && matching_bracket(stack.top(),*curr)) {
					stack.pop();
				} else 
						return false;
			}
	}

  return stack.empty();
}

int main() {
	assert(check("{ [ (2 * 3) ] } }") == false);
	assert(check("{[()]}") == true);
	assert(check("") == true);
	assert(check(nullptr) == false);
	assert(check("{{[{}]}{[]}[]}") == true);
	assert(check("{ 1 + [ 2 * ( 3 / 2) ] } + [1 + (3 * 5) ]") == true);

	return 0;
}
