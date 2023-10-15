#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class myStack {

    vector<int> buffer;
    size_t top;
    size_t size;

public:
    myStack(){
        top = 0;
        size = 0;
    }

    long long push(int i) {
        if(buffer.size() <= size) {
            buffer.push_back(i);
        }
        else
        {
            buffer[top] = i;
        }

        long long res = 0;
        for (int i = top - 1; i >= 0; i--) {
            if(buffer[i] <= buffer[i + 1]) {
                res += buffer[i + 1] + 1 - buffer[i];
                buffer[i] = buffer[i + 1] + 1;
            } else {
                break;
            }
        }
        top++;
        size++;
        return res;
    }
};

int main()
{
    myStack right;
    myStack left;

    long long min_d = 0x7FFFFFFFFFFFFFFF;

    int n;
    
    long long sum = 0;
    cin >> n;
    vector<int> buffer(n);
    vector<long long> ld(n);
    vector<long long> rd(n);
    for (int i = 0; i < n; i++) {
        cin >> buffer[i];
        sum += buffer[i];
        
    }

    for (int i = 0; i < n; i++) {
        if(i != 0)
            ld[i] = ld[i - 1] + left.push(buffer[i]);
        else
            ld[i] = left.push(buffer[i]);
    }

    for (int i = n - 1; i >= 0; i--) {
        if(i != n - 1)
            rd[i] = rd[i + 1] + right.push(buffer[i]);
        else
            rd[i] = right.push(buffer[i]);
    }

    for (int i = 0; i < n; i++) {
        if(ld[i] + rd[i] < min_d) {
            min_d = ld[i] + rd[i];
        }
    }

    cout << sum + min_d << endl;
    return 0;
}