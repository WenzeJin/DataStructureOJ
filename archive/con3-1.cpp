#include <iostream>

#define INF 0x7FFFFFFF
using namespace std;

int map[1001][1001], dis[1001], book[1001];

int main()
{
	int i, j, n, m, t1, t2, t3, cur, v, min, s;
	cin >> n >> m >> s;
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
		dis[i] = map[s][i];
		book[i] = 0;
	}
	//从源点开始
	book[s] = 1;
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
        if(min != INF) {
            book[cur] = 1;
		    for (v = 1; v <= n; v++) {
                if (map[cur][v] < INF) {
                    if (dis[v] > dis[cur] + map[cur][v]) {
                        dis[v] = dis[cur] + map[cur][v];
                    }
                }
		    }
        } else {
            break;
        }
    }

    for (int i = 1; i <= n; i++) {
        if(!book[i]) {
            cout << -1 << endl;
            exit(0);
        }
    }

    int max = 0;
    for(i = 1; i <= n; i++) {
        if(dis[i] > max) {
            max = dis[i];
        }
    }
    cout << (max == INF ? -1 : max) << endl;
    return 0;
}
