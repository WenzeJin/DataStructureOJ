#include <iostream>
#include <cmath>
#include <cstdlib>
#include <utility>
#include <cstdio>
#include <algorithm>

using namespace std;

pair<int, int> position[501];

bool havephone[501];

struct Distance {
    int a;
    int b;
    long long distance;
};

int cmpsmalldistance(Distance a, Distance b) {
    return a.distance < b.distance;
}

int cmpbigll(long long a, long long b)
{
    return a > b;
}

Distance disbuff[501 * 501];

//double map[501][501];

long long result[501];

class UnionSet {
private:
    int parent[501];
public:
    UnionSet(int n) {
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] == x) {
            return x;
        }
        return parent[x] = find(parent[x]);
    }

    void merge(int x, int y) {
        int fx = find(x);
        int fy = find(y);
        if (fx != fy) {
            parent[fx] = fy;
        }
    }
};

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> position[i].first >> position[i].second;
    }

    int index = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            disbuff[index].a = i;
            disbuff[index].b = j;
            disbuff[index].distance = abs(position[i].first - position[j].first) + abs(position[i].second - position[j].second);
            index++;
        }
    }



    sort(disbuff, disbuff + index, cmpsmalldistance);
    // kruskal
    UnionSet us(n);

    int cnt = 0;
    for (int i = 0; i < index; i++)
    {
        if (us.find(disbuff[i].a) != us.find(disbuff[i].b)) {
            us.merge(disbuff[i].a, disbuff[i].b);
            result[cnt++] = disbuff[i].distance;
        }
    }


    sort(result, result + cnt, cmpbigll);

    long long res = result[0];

    if(res % 2 == 0) {
        res = res / 2;
    } else {
        res = res / 2 + 1;
    }

    printf("%d\n", res);
}
