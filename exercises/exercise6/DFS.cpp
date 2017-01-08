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
 * and ai bi means there is an edge ai->bi and also bi->ai.
 * ai and bi are numbers from 0 to N-1
 *
 * Output: True if there is a cycle in the graph from the input or False if there isn't
 * The graph is undirected, cycle - cycle with at least 3 edges in it
 */
#include <iostream>
#include <vector>
using std::vector;

bool DFS(int v, int prev, const vector < vector<int>>& g, vector<bool>& used) {
	used[v] = true;
	int currV;
	for (int i = 0; i < g[v].size(); i++) {
		currV = g[v][i];
		if (!used[currV]) {
			if (DFS(currV, v, g, used)) {
				return true;
			}
		}
		else if (used[currV] && currV != prev) {
			return true;
		}
		//std::cout << currV << std::endl;
	}
	return false;
}
/*
Cycle:
6 6
0 1
0 2
2 3
1 3
1 4
3 5

No cycle:
6 5
0 1
0 2
2 3
1 4
3 5
*/

int main() {
	vector<vector<int>> g;
	int n, m;
	int from, to;
	std::cin >> n >> m;
	g.resize(n);
	for (int i = 0; i < m; i++) {
		std::cin >> from >> to;
		g[from].push_back(to);
		g[to].push_back(from);
	}
	vector<bool> used(n);

	bool res = false;
	for (int i = 0; i < n && !res; i++) {
		if (!used[i]) {
			res = DFS(i, i, g, used);
		}
	}
	std::cout << std::boolalpha << res << std::endl;
	return 0;
}