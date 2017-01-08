/*
 * Problem: Input a Graph in the following way:
 * N M
 * a1 b1
 * a2 b2
 * .....
 * am bm
 *
 * where:
 * N is the number of vertices
 * M is the number of edges
 * and ai bi means there is an edge ai->bi (and also bi->ai).
 * ai and bi are numbers from 0 to N-1
 *
 * Output: Print the vertices at each level in the graph from the starting one - 0
 * Example:
 * vertices at level 0: x1..xk
 * vertices at level 1: .....
 * .......................
 * vertices at level p: .....
 */
#include <iostream>
#include <queue>
#include <vector>


void BFS(const std::vector<std::vector<int>>& graph) {
	bool used[1000000];
	memset(used, 0, sizeof(used));
	std::queue<int> q;

	used[0] = true;
	q.push(0);

	int level = 0, count = 1;
	int currV, newV;
	std::cout << "vertices at level " << level << ": ";
	while (!q.empty()) {
		currV = q.front();
		q.pop();
		count--;
		std::cout << currV << ", ";
		for (int to : graph[currV]) {
			if (!used[to]) {
				q.push(to);
				used[to] = true;
			}
		}
		if (count == 0) {
			level++;
			count = q.size();
			if (count > 0) {
				std::cout << std::endl << "vertices at level " << level << ": ";
			}
			else {
				std::cout << std::endl;
			}
		}
	}
}

int main() {
	/// start - 0
	int N, M;
	std::cin >> N >> M;
	std::vector<std::vector<int>> graph;
	graph.resize(N);
	int from, to;
	for (int i = 0; i < M; i++) {
		std::cin >> from >> to;
		graph[from].push_back(to);
		graph[to].push_back(from);
	}
	BFS(graph);
}
