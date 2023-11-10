#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
const int INF = 0x3f3f3f3f;
int a[N], m[N], n;
int res = -INF;
void dfs(int u)
{
    if ((u << 1) > n)
    {
        m[u] = a[u];
        res = max(res, m[u]);
        return;
    }
    dfs(u << 1);
    dfs(u << 1 | 1);
    m[u] = max(0, max(m[u << 1], m[u << 1 | 1])) + a[u];
    res = max(res, max(m[u], m[u << 1] + m[u << 1 | 1] + a[u]));
    return;
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    dfs(1);
    cout << res << endl;
    return 0;
}