#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

bool map[10001][10001];
bool visited[10001];
int dfn[10001], low[10001], sta[10001], vis[10001], st1[10001];
int dn;
int tt, scc;
int N, M; // N for vertex, M for edge

vector<int> ans;
vector<int> tmp;

void dfs(int cur) {
	visited[cur] = true;
	tmp.push_back(cur);
	for (int i = 0; i < N; i++)
	{
		if(map[cur][i] && map[i][cur] && !visited[i]) {
			dfs(i);
		}
	}
}

/**/
void tarjan(int u)
{
	dfn[u] = low[u] = ++ dn; // 将 dfn 和 low 都赋值为编号 dn
	sta[++tt] = u, vis[u] = 1, st1[u] = 1;
	// 将当前点 u 加入栈中，标记为访问过，已经入栈
	for (int i = 0; i < N; i++)
	{
		if(map[u][i]) {
			int j = i;
			if (!vis[j]) // 如果这个点还没有被访问过，就访问
			{
				tarjan(j); // 继续搜这个点的儿子节点
				low[u] = min(low[u], low[j]);
				// 更新这个点的 low 值为 low[u] 和 low[j] 的较小值
			}
			else if (st1[j]) // 如果这个点已经在栈中了
				low[u] = min(low[u], dfn[j]);
				// 那么就把这个点和这个子节点的 dfn 取最小值
		}
		
	}
	int t;
	if (dfn[u] == low[u])
	// dfn[u] == low[u] 表示 u 是一个强连通分量的跟根
	{
		scc++;
		// 统计连通分量的个数
		do
		{
			t = sta[tt -- ];
			st1[t] = 0;
			// 取出，标记为不在栈中
			tmp.push_back(t);
		} while (u != t);
		if (tmp.size() > ans.size()) {
			ans = tmp;
		}
		tmp.clear();
		//	输出最大强连通分量
	}
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		int t1, t2;
		cin >> t1 >> t2;
		map[t1][t2] = true;
	}

	for (int i = 0; i < N; i++) {
		map[i][i] = true;
	}

	for (int i = 0; i < N; i++)
	{
		if (!visited[i]) {
			tarjan(i);
		}
	}

	sort(ans.begin(), ans.end());

	for (int i = 0; i < ans.size(); i++)
	{
		cout << ans[i] << " ";
	}
	cout << endl;
}