#include <iostream>
#include <cassert>
#define ts UnionSet::trans

using namespace std;

template<typename T>
class Deque {

    struct Node {
        T val;
        Node *prev;
        Node *next;
    };

    Node *head;
    size_t _size;

public:

    Deque() {
        head = new Node();
        head->prev = head;
        head->next = head;
        _size = 0;
    }

    ~Deque() {
        Node *pt = head->next;
        while(pt != head) {
            pt = pt->next;
            delete pt->prev;
        }
        delete pt;
        head = nullptr;
    }

    void push_front(T& v) {
        Node *temp = new Node();
        temp->val = v;
        temp->prev = head;
        temp->next = head->next;
        head->next = temp;
        temp->next->prev = temp;
        _size++;
    }

    void push_back(T& v) {
        Node *temp = new Node();
        temp->val = v;
        temp->next = head;
        temp->prev = head->prev;
        head->prev = temp;
        temp->prev->next = temp;
        _size++;
    }

    T front() {
        assert(_size > 0);
        return head->next->val;
    }

    T back() {
        assert(_size > 0);
        return head->prev->val;
    }

    void pop_front() {
        assert(_size > 0);
        Node *old = head->next;
        head->next = old->next;
        head->next->prev = head;
        delete old;
        _size--;
    }

    void pop_back() {
        assert(_size > 0);
        Node *old = head->prev;
        head->prev = old->prev;
        head->prev->next = head;
        delete old;
        _size--;
    }

    bool empty() {
        return _size == 0;
    }

    size_t size() {
        return _size;
    }
};

class UnionSet {
    int *parent;

public:

    static inline int trans(int id) {
        return id + 1;
    }

    UnionSet(size_t peopleNumber) {
        parent = new int[peopleNumber + 3];
        for (int i = 0; i < peopleNumber + 3; i++) {
            parent[i] = -1;
        }
    }

    bool findEqual(int p1, int p2) {
        while(parent[p1] >= 0) {
            p1 = parent[p1];
        }
        while(parent[p2] >= 0) {
            p2 = parent[p2];
        }
        return p1 == p2;
    }

    int find(int p) {
        while(parent[p] >= 0) {
            p = parent[p];
        }
        return p;
    }

    bool UnionAgainst(int p1, int p2) {
        if(parent[p1] < 0 && parent[p2] < 0) {
            parent[p1] = 1;
            parent[p2] = 0;
            return true;
        }
        if (parent[p1] < 0)
        {
            int test = find(p2);
            if (test)
            {
                parent[p1] = 0;
            }
            else
            {
                parent[p1] = 1;
            }
            return true;
        }
        if (parent[p2] < 0)
        {
            int test = find(p1);
            if(test) {
                parent[p2] = 0;
            } else {
                parent[p2] = 1;
            }
            return true;
        }
        return !findEqual(p1, p2);
    }
};


int main() {
    int num, cases;

    cin >> num >> cases;

    UnionSet buffer(num);

    if(cases >= num) {
        cout << "false" << endl;
        return 0;
    }

    Deque<pair<int, int> > rst;

    int lastlay = 0;
    int currlay = 0;
    bool pushed = false;

    for (int i = 0; i < cases; i++) {
        int p1, p2;
        cin >> p1 >> p2;
        if(buffer.find(ts(p1)) == ts(p1) && buffer.find(ts(p2)) == ts(p2)) {
            if(pushed) {
                pair<int, int> temp;
                temp.first = p1;
                temp.second = p2;
                rst.push_back(temp);
                lastlay++;
            } else {
                buffer.UnionAgainst(ts(p1), ts(p2));
                pushed = true;
            }
        } else if(!buffer.UnionAgainst(ts(p1), ts(p2))) {
            cout << "false" << endl;
            return 0;
        }
    }

    while(lastlay) {
        currlay = 0;
        pushed = false;
        for (int i = 0; i < lastlay; i++)
        {
            pair<int, int> tp = rst.front();
            rst.pop_front();
            int p1 = tp.first, p2 = tp.second;
            if(buffer.find(ts(p1)) == ts(p1) && buffer.find(ts(p2)) == ts(p2)) {
                if(pushed) {
                    pair<int, int> temp;
                    temp.first = p1;
                    temp.second = p2;
                    rst.push_back(temp);
                    currlay++;
                } else {
                    buffer.UnionAgainst(ts(p1), ts(p2));
                    pushed = true;
                }
            } else if(!buffer.UnionAgainst(ts(p1), ts(p2))) {
                cout << "false" << endl;
                return 0;
            }
        }
        lastlay = currlay;
    }

    cout << "true" << endl;

    return 0;
}

