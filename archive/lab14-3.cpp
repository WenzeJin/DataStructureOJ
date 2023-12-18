#include <iostream>
#include<fstream>
#define INF 999999999
using namespace std;

int map[1001][1001], dis[1001], book[1001];
int disback[1001], bookback[1001];

int main()
{
	int i, j, n, m, t1, t2, t3, cur, v, min;
	cin >> n >> m;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			if (i == j) map[i][j] = 0;
			else map[i][j] = INF;
		}
	}
	for (i = 1; i <= m; i++) {
		cin >> t1 >> t2 >> t3;
		map[t1][t2] = t3;
	}
	//初始化dis数组,代表源点到其他顶点的初始路程
	for (i = 1; i <= n; i++) {
		dis[i] = map[1][i];
		book[i] = 0;
	}
	//从源点开始
	book[1] = 1;
	//Dijkstra算法核心代码--贪心策略
	for (i = 1; i <= n - 1; i++) { // 总共需要更新n-1次，对除去源点以外的n-1个点进行松弛
		//寻找距离源点最近的顶点
		min = INF;
		for (j = 1; j <= n; j++) {
			if (book[j] == 0 && dis[j] < min) {
				min = dis[j];
				cur = j;
			}
		}
		//cur代表距离源点最近的
		book[cur] = 1;
		for (v = 1; v <= n; v++) {
			if (map[cur][v] < INF) {
				if (dis[v] > dis[cur] + map[cur][v]) {
					dis[v] = dis[cur] + map[cur][v];
				}
			}
		}
	}

    for (i = 1; i <= n; i++)
    {
        disback[i] = map[i][1];
        bookback[i] = 0;
    }
    bookback[1] = 1;
    
    for (i = 1; i <= n - 1; i++) { // 总共需要更新n-1次，对除去源点以外的n-1个点进行松弛
		//寻找距离源点最近的顶点
		min = INF;
		for (j = 1; j <= n; j++) {
			if (bookback[j] == 0 && disback[j] < min) {
				min = disback[j];
				cur = j;
			}
		}
		//cur代表距离源点最近的
		bookback[cur] = 1;
		for (v = 1; v <= n; v++) {
			if (map[v][cur] < INF) {
				if (disback[v] > disback[cur] + map[v][cur]) {
					disback[v] = disback[cur] + map[v][cur];
				}
			}
		}
	}

    int sum = 0;
    for(i = 1; i <= n; i++) {
        sum += dis[i] + disback[i];
    }
    cout << sum << endl;
    return 0;
}
