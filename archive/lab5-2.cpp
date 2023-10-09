//单调队列 前缀和

#include <iostream>
#include <cassert>
#include <queue>

using namespace std;

int arr[1000000];
long long pre[1000000];
long long k;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int cnt;
        cin >> cnt >> k;

        for (int i = 1; i <= cnt; i++){
            cin >> arr[i];
        }

        pre[0] = 0;
        for (int i = 1; i <= cnt; i++) {
            pre[i] = arr[i] + pre[i - 1];
        }

        deque<int> que;
        int res = cnt + 1;

        for (int i = 0; i <= cnt; i++) {
            int currsum = pre[i];
            while(!que.empty() && currsum - pre[que.front()] >= k) {
                res = min(res, i - que.front());
                que.pop_front();
            }
            while(!que.empty() && pre[que.back()] >= currsum) {
                que.pop_back();
            }
            que.push_back(i);
        }

        if (res == cnt + 1)
        {
            res = -1;
        }
        cout << res << endl;
    }
}