#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

namespace graph {

struct edge {
	int w{0};
	int vertex_index;
};

template <typename T>
struct vertex {
	bool visited{false};
	T data;
	int parent;
	std::vector<edge> adj;
};

template <typename T>
struct graph {
	std::vector<vertex<T>> vertices;
	
	graph(int number_of_vertices) {
		for (int i=0; i < number_of_vertices; ++i)
			vertices.push_back({false, i, -1, {}});
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
			std::cout <<'{' <<v.data <<',' <<v.visited <<',' <<v.parent <<',' <<",{";
			for (const auto& e : v.adj)
				std::cout <<e.vertex_index <<',';
			std::cout <<"}}\n";
		}
	}
	
	void reset_data() {
		for (auto&& v : vertices) {
			v.visited = false;
			v.parent = -1;
		}
	}

	void dfs() {
		reset_data();
			
		for (int i=0; i<vertices.size(); ++i) {	
			if (!vertices[i].visited)
				dfs_visit(i);
		}
	}

	void dfs_visit(int i) {
		for (edge& e : vertices[i].adj)  {
			vertex<T>& curr = vertices[e.vertex_index];
			if (!curr.visited) {
				curr.parent = i;
				dfs_visit(e.vertex_index);
			}
		}
		vertices[i].visited=true;
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
				if (!v.visited) {
					v.parent = curr_index;
					q.push(e.vertex_index);
				}
			}
			u.visited = true;
		}
	}
};

} // namespace graph

int main() {
	graph::graph<int> g{4};
	g.add_edges(0, {1});
	g.add_edges(1, {2});
	g.add_edges(2, {});
	g.add_edges(3, {1,2});

	g.print();
	//g.bfs(0);
	g.dfs();
	std::cout <<'\n';
	//g.revisit(3);
	//std::cout <<g.reachable(0, 3) <<'\n';		
	g.print();

	return 0;
}
