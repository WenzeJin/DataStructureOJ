#include <iostream>
#include <cassert>

using namespace std;

int arr[1000000];
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

        long long sum = 0;
        int left = 0;
        int right = 0;
        int min = cnt + 1;

        if (cnt > 10000) {
            while(right != cnt || sum > k){
                while(right < cnt && sum < k) {
                    right++;
                    sum += arr[right];
                }

                if(sum >= k && right - left < min) {
                    min = right - left;
                }

                while(left < right && sum >= k) {
                    if(right - left < min) {
                        min = right - left;
                    }
                    left++;
                    sum -= arr[left];
                }
            }
        } else {
            for (int left = 1; left <= cnt; left ++) {
                sum = 0;
                for (int right = left; right <= cnt; right++)
                {
                    sum += arr[right];
                    if(sum >= k) {
                        if(right - left + 1 < min) {
                            min = right - left + 1;
                        }
                        break;
                    }
                }
            }
        }

        if(min == cnt + 1){
            min = -1;
        }
        cout << min << endl;
    }
}