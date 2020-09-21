#include <iostream>
#include <vector>
#include <algorithm>

namespace graph {

struct edge {
	int w{0};
	int vertex_index;
};

template <typename T>
struct vertex {
	bool visited{false};
	T data;
	std::vector<edge> adj;
};

template <typename T>
struct graph {
	std::vector<vertex<T>> vertices;
	
	graph(int number_of_vertices) {
		for (int i=0; i < number_of_vertices; ++i)
			vertices.push_back({false, i, {}});
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
			std::cout <<'{' <<v.data <<',' <<v.visited <<",{";
			for (const auto& e : v.adj)
				std::cout <<e.vertex_index <<',';
			std::cout <<"}}\n";
		}
	}

	void revisit(int vertex_index) {
		if  (vertex_index < vertices.size()) {
			vertex<T>& v=vertices[vertex_index];
			if (!v.visited)
				dfs_visit(v);
		}
	}

	void dfs_visit(vertex<T>& v) {
		for (edge& e : v.adj)  {
			vertex<T>& curr = vertices[e.vertex_index];
			if (!curr.visited) {
				curr.visited = true;
				dfs_visit(curr);
			}
		}
	}

	bool reachable(int from, int to) {
		revisit(from);
		return vertices[to].visited;
	}
};

} // namespace graph

int main() {
	graph::graph<int> g{4};
	g.add_edges(0, {1,2});
	g.add_edges(1, {1});
	g.add_edges(2, {});
	g.add_edges(3, {1,2});

	g.print();
	g.revisit(3);
	std::cout <<g.reachable(3, 0) <<'\n';		
	g.print();

	return 0;
}
