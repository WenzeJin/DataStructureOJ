#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>


using namespace std;

long long t, n, c, d, s[200001];
bool cmp(int a, int b) {
    return a > b;
}

bool check(long long k) {
    long long sum = s[min(n, k + 1)] * (d / (k + 1));
    sum += s[min(n, d % (k + 1))];
    return sum >= c;
}

int main() {
    
    scanf("%lld %lld %lld", &n, &c, &d);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &s[i]);
    }
    sort(s + 1, s + n + 1, cmp);
    for(int i = 1; i <= n; i++) {
        s[i] += s[i - 1];
    }
    if(s[min(n, d)] >= c)
        printf("Infinity\n");
    else if(s[1] * d < c)
        printf("Impossible\n");
    else {
        int l = 0, r = d, ans = 0;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(check(mid)) {
                ans = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }
        printf("%lld\n", ans);
    }
}