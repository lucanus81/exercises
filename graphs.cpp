#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

namespace graph {

enum class COLOR { WHITE=0, GRAY=1, BLACK=2 };
const char* colors[]={"WHITE", "GRAY", "BLACK"};

struct edge {
	int w{0};
	int vertex_index;
};

template <typename T>
struct vertex {
	COLOR color;
	T data;
	int parent;
	int d, f;
	std::vector<edge> adj;
};

template <typename T>
struct graph {
	std::vector<vertex<T>> vertices;
	
	graph(int number_of_vertices) {
		for (int i=0; i < number_of_vertices; ++i)
			vertices.push_back({COLOR::WHITE, i, -1, -1, -1, {}});
	}
	
	void add_edges(int vertex, std::initializer_list<int> edges) {
		auto sorter = [](const edge& e1, const edge& e2){ return e1.vertex_index < e2.vertex_index; };

		for (int i : edges)
			if (vertex < vertices.size() && i < vertices.size()) {
				std::vector<edge>& curr = vertices[vertex].adj;
				if (!std::binary_search(curr.begin(), curr.end(), edge{0, i}, sorter)) {
					curr.push_back({0,i});
					std::sort(curr.begin(), curr.end(), sorter);
				}
			}	
	}

	void print() const {
		for (const auto& v : vertices) {
			std::cout <<'{' <<v.data <<',' <<colors[(int)v.color] <<',' <<v.parent <<',' <<v.d <<',' <<v.f <<",{";
			for (const auto& e : v.adj)
				std::cout <<e.vertex_index <<',';
			std::cout <<"}}\n";
		}
	}
	
	void reset_data() {
		for (auto&& v : vertices) {
			v.color = COLOR::WHITE;
			v.parent = -1;
		}
	}

	bool tree_or_forward(vertex<T> const& u, vertex<T> const& v) { return u.d < v.d && v.d < v.f && v.f < u.f; }
	bool back(vertex<T> const& u, vertex<T> const& v) { return v.d <= u.d && u.d < v.f && u.f <= v.f; }
	bool cross(vertex<T> const& u, vertex<T> const& v) { return v.d < v.f && v.f < u.d && u.d < u.f; }

	void classify_edges() {
		for (int i=0; i<vertices.size(); ++i)
			for (const edge& e : vertices[i].adj) {
				vertex<T> const& u = vertices[i];
				vertex<T> const& v = vertices[e.vertex_index];
				char tofe = tree_or_forward(u,v) ? 'T' : '-';
				char be = back(u,v) ? 'B' : '-';
				char ce = cross(u,v) ? 'C' : '-';
				std::cout <<"[" <<u.data <<"," <<v.data <<"]: " <<tofe <<be <<ce <<'\n';	
			}
	}

	void dfs() {
		reset_data();
		int time=0;
			
		for (int i=0; i<vertices.size(); ++i) {	
			if (vertices[i].color == COLOR::WHITE)
				dfs_visit(i, &time);
		}

		classify_edges();
	}

	void dfs_visit(int i, int* time) {
		vertices[i].d = ++*time;
		vertices[i].color = COLOR::GRAY;
		for (edge& e : vertices[i].adj)  {
			vertex<T>& curr = vertices[e.vertex_index];
			if (curr.color == COLOR::WHITE) {
				curr.parent = i;
				dfs_visit(e.vertex_index, time);
			}
		}
		vertices[i].color=COLOR::BLACK;
		vertices[i].f=++*time;
	}

	bool reachable(int from, int to) {
		bfs(from);
		
		vertex<T>& start = vertices[from];
		vertex<T>& curr = vertices[to];
		while (curr.parent != -1 && curr.data != start.data)
			curr = vertices[curr.parent];
		return curr.data == start.data;
	}

  void bfs(int from) {
		reset_data();
		
		std::queue<int> q;
		q.push(from);
		while (!q.empty()) {
			int curr_index = q.front(); q.pop();
			vertex<T>& u = vertices[curr_index];
			for (const edge& e : u.adj) { 
				vertex<T>& v = vertices[e.vertex_index];
				if (v.color == COLOR::WHITE) {
					v.color = COLOR::GRAY;
					v.parent = curr_index;
					q.push(e.vertex_index);
				}
			}
			u.color = COLOR::BLACK;
		}
	}
};

} // namespace graph

int main() {
	graph::graph<int> g{6};
	g.add_edges(0, {1,3});
	g.add_edges(1, {4});
	g.add_edges(2, {4,5});
	g.add_edges(3, {1});
	g.add_edges(4, {3});
	g.add_edges(5, {5});

	g.print();
	//g.bfs(0);
	g.dfs();
	std::cout <<'\n';
	//g.revisit(3);
	//std::cout <<g.reachable(0, 3) <<'\n';		
	g.print();

	return 0;
}
