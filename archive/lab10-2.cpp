#include<map>
#include<set>
#include<iostream>

using namespace std;

class UnionSet {
    unordered_map<int, int> parent;
    int size_max;
public:
    UnionSet(): parent(),size_max(0) {}

    void add(int x) {
        parent[x] = -1;
        if(0 - parent[x] > size_max) {
            size_max = 0 - parent[x];
        }
    }

    int find(int x) {
        while(parent[x] > 0) {
            x = parent[x];
        }
        return x;
    }

    void unionGroup(int x, int y) {
        while(parent[x] > 0) {
            x = parent[x];
        }
        while(parent[y] > 0) {
            y = parent[y];
        }
        if(x == y) {
            return;
        }
        parent[x] = parent[x] + parent[y];
        if(0 - parent[x] > size_max) {
            size_max = 0 - parent[x];
        }
        parent[y] = x;
    }

    int getMax() {
        return size_max;
    }
};




class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        set<int> visited;
        UnionSet buff;
        for(auto x: nums) {
            auto iter = visited.find(x);
            if (iter != visited.end())
            {
                continue;
            }
            visited.insert(x);
            buff.add(x);
            iter = visited.find(x + 1);
            if (iter != visited.end())
            {
                buff.unionGroup(x, x - 1);
            }
            if(iter != visited.end()) {
                buff.unionGroup(x, x + 1);
            }
        }

        return buff.getMax();
    }
};

int main() {
    Solution temp;
    vector<int> question = { 4, 0, -4, -2, 2, 5, 2, 0, -8, -8, -8, -8, -1, 7, 4, 5, 5, -4, 6, 6, -3 };
    int ans = temp.longestConsecutive(question);
    cout << ans << endl;
}