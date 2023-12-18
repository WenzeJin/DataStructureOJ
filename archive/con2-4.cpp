#include <iostream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <algorithm>

using namespace std;

int main() {

    int N, S, K;

    cin >> N >> S >> K;

    vector<int> index(N);

    vector<int> post_sum(N + 1);

    for (int i = 0; i < N; i++) {
        int p, a;
        cin >> p >> a;
        post_sum[i + 1] = post_sum[i] + a;
        index[i] = p;
    }

    int left = S - K / 2;
    int right = left + K / 2 + K % 2;

    int reright = S + K / 2;
    int releft = reright - K / 2 - K % 2;

    int m = 0;
    int sumleft;
    int sumright;

    while(left <= S) {
        if(left > 0 || releft > 0) {
            sumleft = post_sum[upper_bound(index.begin(), index.end(), right) - index.begin()] - post_sum[lower_bound(index.begin(), index.end(), left) - index.begin()];
            sumright = post_sum[upper_bound(index.begin(), index.end(), reright) - index.begin()] - post_sum[lower_bound(index.begin(), index.end(), releft) - index.begin()];
            if(sumleft > sumright) {
                if(sumleft > m) {
                    m = sumleft;
                }
            } else {
                if(sumright > m) {
                    m = sumright;
                }
            }
        }

        left++;
        right += 2;
        reright--;
        releft-=2;
    }

    cout << m << endl;
}