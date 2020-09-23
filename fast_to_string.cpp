#include <string>
#include <iostream>
#include <limits>
#include <type_traits>
#include <cstdlib>

template <typename T, typename = std::enable_if_t<std::is_integral_v<T>>>
std::string to_string(T i) {
    constexpr int max = std::numeric_limits<T>::digits10 + 2;
    char buffer[max]={};
    int start=max;
		bool negative=i<0;

		do {
        T q = i/10;
        T r = i%10;
        buffer[--start] = static_cast<char>('0'+(negative ? -r : r));
        i = q;
    } while (i);

    if (negative) 
			buffer[--start]='-';
    return {&buffer[start], &buffer[max]};
}

int main() {
		std::cout <<to_string(std::numeric_limits<int>::min()) <<std::endl;
		std::cout <<std::numeric_limits<int>::min() <<std::endl;

		std::cout <<std::numeric_limits<char>::digits10 <<'\n';
		std::cout <<std::numeric_limits<short>::digits10 <<'\n';
		std::cout <<std::numeric_limits<int>::digits10 <<'\n';
		std::cout <<std::numeric_limits<long>::digits10 <<'\n';
		std::cout <<std::numeric_limits<long long>::digits10 <<'\n';
    return 0;
}
