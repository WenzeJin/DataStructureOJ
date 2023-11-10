#include <iostream>
#include <cassert>
#define LC(pos) 2 * pos
#define RC(pos) 2 * pos + 1
#define PA(pos) pos / 2

using namespace std;

struct TreeNode {
    int val;
    TreeNode *lc;
    TreeNode *rc;
    TreeNode *parent;
};

TreeNode *head;

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

void setParent(TreeNode *root) {
    if(root->lc) {
        setParent(root->lc);
        root->lc->parent = root;
    }
    if(root->rc) {
        setParent(root->rc);
        root->rc->parent = root;
    }
}

int countNodes(TreeNode *root, TreeNode *prev) {
    int ans = 0;
    if(root) {
        ans++;
        if(root->parent && root->parent != prev) {
            ans += countNodes(root->parent, root);
        }
        if(root->lc && root->lc != prev) {
            ans += countNodes(root->lc, root);
        }
        if(root->rc && root->rc != prev) {
            ans += countNodes(root->rc, root);
        }
    }
    return ans;
}

bool checkWin(TreeNode *player1) {
    int parent = 0;
    int leftChild = 0;
    int rightChild = 0;
    if (player1 -> parent) {
        parent = countNodes(player1->parent, player1);
    }
    if (player1 -> lc) {
        leftChild = countNodes(player1->lc, player1);
    }
    if (player1 -> rc) {
        rightChild = countNodes(player1->rc, player1);
    }

    if (parent > leftChild + rightChild + 1)
        return true;
    if (leftChild > parent + rightChild + 1)
        return true;
    if (rightChild > leftChild + parent + 1)
        return true;

    return false;
}

int main() {
    int n, player1;
    cin >> n >> player1;

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

    TreeNode *p1node = head;

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
                if(inbuff[inbuff_ind] == player1) {
                    p1node = curr->lc;
                }
            }
            inbuff_ind++;
            if(inbuff[inbuff_ind] != -1) {
                curr->rc = new TreeNode();
                curr->rc->val = inbuff[inbuff_ind];
                buff.push_back(curr->rc);
                curr_layer++;
                if(inbuff[inbuff_ind] == player1) {
                    p1node = curr->rc;
                }
            }
            inbuff_ind++;
        }
        last_layer = curr_layer;
    }

    setParent(head);

    cout << (checkWin(p1node) ? "true" : "false") << endl;

    return 0;
}