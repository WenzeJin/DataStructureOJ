#include <cmath>
#include <iostream>
#include <cassert>

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

struct TreeNode {
    int val;
    int depth;
    TreeNode *lc;
    TreeNode *rc;
};

TreeNode *head;

bool checkAVL(TreeNode *head) {
    if(!head) {
        return true;
    }
    if(head->lc && head->lc->val >= head->val) {
        return false;
    }
    if(head->rc && head->rc->val <= head->val) {
        return false;
    }
    if(head->lc) {
        if(!checkAVL(head->lc))
            return false;
    }
    if(head->rc) {
        if(!checkAVL(head->rc))
            return false;
    }
    int dleft = head->lc ? head->lc->depth : 0;
    int dright = head->rc ? head->rc->depth : 0;
    head->depth = max(dleft, dright) + 1;
    if(abs(dleft - dright) > 1) {
        return false;
    }
    return true;
}

int main() {
    int n;
    cin >> n;

    int *inbuff = new int[2 * n + 1];

    for (int i = 0; i < 2 * n + 1; i ++) {
        cin >> inbuff[i];
    }

    Deque<TreeNode*> buff;
    head = new TreeNode();
    head->val = inbuff[0];
    int last_layer = 1;
    int curr_layer = 0;
    buff.push_back(head);
    int inbuff_ind = 1;

    while(!buff.empty()) {
        curr_layer = 0;
        for (int i = 0; i < last_layer; i++) {
            TreeNode* curr = buff.front();
            buff.pop_front();
            if (inbuff[inbuff_ind] != -1)
            {
                curr->lc = new TreeNode();
                curr->lc->val = inbuff[inbuff_ind];
                buff.push_back(curr->lc);
                curr_layer++;
            }
            inbuff_ind++;
            if(inbuff[inbuff_ind] != -1) {
                curr->rc = new TreeNode();
                curr->rc->val = inbuff[inbuff_ind];
                buff.push_back(curr->rc);
                curr_layer++;
            }
            inbuff_ind++;
        }
        last_layer = curr_layer;
    }
    
    bool res = checkAVL(head);

    if(res) {
        cout << "yes" << endl;
    } else {
        cout << "no" << endl;
    }

    return 0;
}

