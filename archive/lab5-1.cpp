//DFS

#include <iostream>

using namespace std;

int arr[100];
int used[21];
int n;

bool check(){
    for (int i = 0; i < 2 * n - 1; i++){
        if(arr[i] == 0) {
            return false;
        }
    }
    return true;
}

int dfs(int depth) {
    if(depth == n - 1) {
        int pt = 0;
        while(arr[pt]){
            pt++;
        }
        int cand = n;
        while(used[cand] && cand >= 1) {
            cand--;
        }
        if(cand != 1 && arr[pt + cand] != 0) {
            return 0;
        }
        arr[pt] = cand;
        if(cand != 1) {
            arr[pt + cand] = cand;
        }

        if (check()) {
            return 1;
        }
        else
        {
            used[cand] = 0;
            arr[pt] = 0;
            if(cand != 1)
                arr[pt + cand] = 0;
            return 0;
        }
    } else {
        int pt = 0;
        while(arr[pt]){
            pt++;
        }

        for (int cand = n; cand >= 1; cand --){
            if(!used[cand]){
                if(cand != 1 && (arr[pt + cand] == 0 && pt + cand < 2 * n - 1)){
                    arr[pt] = cand;
                    arr[pt + cand] = cand;
                    used[cand] = 1;

                    if (dfs(depth + 1)) {
                        return 1;
                    }
                    arr[pt] = 0;
                    arr[pt + cand] = 0;
                    used[cand] = 0;
                } else if (cand == 1) {
                    arr[pt] = 1;
                    used[1] = 1;

                    if (dfs(depth + 1)) {
                        return 1;
                    }
                    arr[pt] = 0;
                    used[1] = 0;
                }
            }
        }
        return 0;
    }
}

int main() {
    cin >> n;
    dfs(0);
    for (int i = 0; i < 2 * n - 1; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}