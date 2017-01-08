/* Problem: https://drive.google.com/file/d/0B4I_u6R4z8DRUUtvUDdncWlNLXM/view?usp=sharing 
*/
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <iostream>
using std::queue;

struct Pass {
	char pass[6];
	bool operator == (const Pass &other) const {
		return strcmp(pass, other.pass) == 0;
	}
};


int BFS(Pass start, Pass end, bool *used) {

	std::queue<Pass> q;

	Pass current, newPass, newDigits;
	int count = 1, level = 0, num;
	q.push(start);
	used[atoi(start.pass)] = true;

	while (!q.empty()) {
		current = q.front();
		q.pop();
		if (current == end) {
			return level;
		}
		count--;
		for (int i = 0; i < 5; i++) {
			strcpy(newDigits.pass, current.pass);
			if (current.pass[i] == '9') {
				newDigits.pass[i] = '0';
			}
			else {
				newDigits.pass[i]++;
			}
			num = atoi(newDigits.pass);
			if (!used[num]) {
				used[num] = true;
				q.push(newDigits);
			}
		}

		for (int i = 0; i < 5; i++) {
			strcpy(newDigits.pass, current.pass);
			if (current.pass[i] == '0') {
				newDigits.pass[i] = '9';
			}
			else {
				newDigits.pass[i]--;
			}
			num = atoi(newDigits.pass);
			if (!used[num]) {
				used[num] = true;
				q.push(newDigits);
			}
		}
		if (count == 0) {
			level++;
			count = q.size();
		}
	}
	return -1;
}
/*
int main() {
	bool used[100010];
	memset(used, 0, sizeof(used));

	char buffer[6];
	int N;
	Pass start, end;
	scanf("%s", &start.pass);//std::cin>>start.pass;
	scanf("%s", &end.pass);
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", buffer);
		used[atoi(buffer)] = true;
	}
	printf("%d\n", BFS(start, end, used));
	return 0;
}*/