/* Problem: https://drive.google.com/file/d/0B4I_u6R4z8DRRmdEdjZQZXVlaEU/view?usp=sharing
*/
#include <cstdio>
#include <iostream>
#include <queue>
int N, M, T;

struct Apple {
	Apple(int row = 0, int col = 0) : row(row), col(col) {}
	int row, col;
};
void BFS(Apple fstApple, Apple sndApple) {
	bool used[1000][1000];
	memset(used, 0, sizeof(used));
	std::queue<Apple> q;

	int dx[4] = { 0, +1, 0, -1 };
	int dy[4] = { -1, 0, +1, 0 };

	used[fstApple.row][fstApple.col] = true;
	q.push(fstApple);
	if (sndApple.row >= 0) {
		used[sndApple.row][sndApple.col] = true;
		q.push(sndApple);
	}

	int rottenCount = q.size();
	int level = 0, count = rottenCount;
	int currRow, currCol, newRow, newCol;
	while (!q.empty() && level < T) {
		///std::cout << "count: " << rottenCount << std::endl;
		currRow = q.front().row;
		currCol = q.front().col;
		q.pop();
		count--;
		for (int i = 0; i < 4; i++) {
			newRow = currRow + dy[i];
			newCol = currCol + dx[i];
			if (newRow >= 0 && newCol >= 0 && newRow < N && newCol < M && !used[newRow][newCol]) {
				used[newRow][newCol] = true;
				q.push(Apple(newRow, newCol));
				///std::cout << newRow << "  -  " << newCol << std::endl;
			}
		}
		if (count == 0) {
			level++;
			rottenCount += q.size();
			count = q.size();
		}
	}

	std::cout << N*M - rottenCount << std::endl;
}

int main() {
	apple fstapple, sndapple;
	std::cin >> n >> m >> t;
	std::cin >> fstapple.row >> fstapple.col;
	fstapple.row--; fstapple.col--;
	std::cin >> sndapple.row;
	if (std::cin) {
		std::cin >> sndapple.col;
		sndapple.row--; sndapple.col--;
	}
	if (!std::cin) {
		sndapple = apple{ -1,-1 };
	}

	bfs(fstapple, sndapple);
	return 0;
}
