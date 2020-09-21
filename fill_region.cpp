#include <iostream>

template <typename T, int N, int M>
struct Matrix {
	T pixels[N][M]={};
  static constexpr int width = N;
  static constexpr int height = M;
  
	void print() const {
		for (int x=0; x<width; ++x) {
			for (int y=0; y<height; ++y)
				std::cout <<pixels[x][y];
      std::cout <<'\n';
    }
  }
};

template <typename T, int N, int M>
void fill_rec(Matrix<T,N,M>& screen, int x, int y, T initial_color, T color) {
  if (x < 0 || x >= N || y < 0 || y >= M)
		return;
  if (screen.pixels[x][y] != initial_color) 
    return;
    
  screen.pixels[x][y] = color;
  fill_rec(screen, x - 1, y, initial_color, color);
  fill_rec(screen, x + 1, y, initial_color, color);
  fill_rec(screen, x, y - 1, initial_color, color);
  fill_rec(screen, x, y + 1, initial_color, color);
}

int main() {
  Matrix<int,5,10> screen{{1,1,1,1,0,1,1,1,1,1,
                           1,0,0,1,0,1,0,0,0,1,
                           1,0,0,1,1,1,0,0,0,1,
                           1,0,0,0,0,0,0,0,0,1,
                           1,1,1,1,1,1,1,1,1,1}};
  screen.print();
    
  int initial_x=1, initial_y=1;
  int new_fill_color = 8;
  fill_rec(screen, 
           initial_x, initial_y, 
           screen.pixels[initial_x][initial_y], 
           new_fill_color);  
  std::cout <<'\n';
  screen.print();

  return 0;
}


