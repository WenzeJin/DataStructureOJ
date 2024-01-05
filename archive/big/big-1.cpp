/*
	DATA STRUCTURE: Program Assignment 1
	Created by 金文泽 221220028.
*/

#include<iostream>

using namespace std;

int hash_area[1000002];
int map[1001][1001];
int N;
int area;
int dir[4][2] = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };

/*
	0: sea, 1: unvisited island, 2~: visited island.
	All the tags of the islands are unique.
	The tag is the key of hash_area, and the value is the area of the island.
*/ 
int getTag(int x, int y) {
	return x * N + y + 2;	// 0, 1 is reserved for sea and unvisited island
}

/*
	DFS to find the area of the island.
	After DFS, the island will be marked as visited.
*/
void dfs(int i, int j, int tag) {
	if (i < 0 || i >= N || j < 0 || j >= N) return;
	if (map[i][j] != 1) return;
	map[i][j] = tag;
	area++;
	dfs(i - 1, j, tag);
	dfs(i + 1, j, tag);
	dfs(i, j - 1, tag);
	dfs(i, j + 1, tag);
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	hash_area[0] = 0;	// sea will be regarded as an island of 0 area.
	hash_area[1] = 0;	// unvisited island will be regarded as an island of 0 area.

	// DFS to find the area of each island and tag it.
	for (int i = 0; i < N; i++) {
		for (int j = 0;j < N; j++) {
			if (map[i][j] == 1) {
				area = 0;
				int tag = getTag(i, j);
				dfs(i, j, tag);
				hash_area[tag] = area;
			}
		}
	}

	// Enumerate all space with 0, try to add the areas of all the islands around it.
	int max_area = 0;
	for (int i = 0; i < N; i++) {
		for (int j = 0;j < N; j++) {
			if (map[i][j] == 0) {
				int area = 1;
				int visited[4] = { 0 };
				int visited_cnt = 0;
				for (int k = 0; k < 4; k++) {
					int x = i + dir[k][0];
					int y = j + dir[k][1];
					if (x < 0 || x >= N || y < 0 || y >= N) continue;
					bool flag = true;
					for (int i = 0; i < visited_cnt; i++) {
						if (visited[i] == map[x][y]) {
							flag = false;
							break;
						}
					}
					if(flag)
						area += hash_area[map[x][y]];
						visited[visited_cnt++] = map[x][y];
				}
				if(area > max_area)
					max_area = area;
			}
		}
	}

	cout << max_area << endl;
}