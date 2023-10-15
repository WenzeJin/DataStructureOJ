#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    deque<int> num;
    int k;
    int n;
    cin >> n >> k;
    vector<int> buffer(n);
    for (int i = 0; i < n; i++) {
        cin >> buffer[i];
    }
    for(auto each: buffer) {
        if(num.empty()){
            num.push_back(each);
        } else {
            while(!num.empty() && num.back() > each && k > 0) {
                num.pop_back();
                k--;
            }
            num.push_back(each);
        }
        while(!num.empty() && num.front() == 0) {
            num.pop_front();
        }

        
    }

    if(num.empty()) {
        cout << 0 << endl;
        return 0;
    }

    while(!num.empty()) {
        cout << num.front();
        num.pop_front();
    }
    
    cout << endl;
    return 0;
}