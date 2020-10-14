#include <iostream>
#include <memory>

template <typename T>
struct deleter {
	void operator()(T* ptr) { if (ptr != nullptr) { delete ptr; } }
};

template <typename T, typename Deleter=deleter<T>>
struct smart {
private:
	T* ptr_;
	Deleter d;

public:
	smart() : ptr_{nullptr} {}
	explicit smart(T* ptr) : ptr_{ptr} {}
	~smart() { d(ptr_); }
	smart(smart<T,Deleter> const&) = delete;
	smart& operator=(smart<T,Deleter> const&) = delete;
	smart& operator=(smart<T,Deleter>&& s) {
		if (this != &s) {
			d(ptr_);
			ptr_ = std::move(s.ptr_);
			s.ptr_ = nullptr;
		}
		
		return *this;		
	}
	smart(smart<T,Deleter>&& s) : ptr_{std::move(s.ptr_)} {}
	T& operator*() const { return *ptr_; }
	T* operator->() const { return ptr_; }
	T* get() const { return ptr_; }
};


int main() {
	smart<int> s{new int{3}};
	std::cout <<*s <<'\n';
	
	smart<int> r;
	if (r.get() != nullptr)
		std::cout <<"error\n";
	return 0;
}
