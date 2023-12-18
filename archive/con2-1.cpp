#include <iostream>
#include <cassert>
#include <deque>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode *parent;
};

using namespace std;

TreeNode *head;

void cal(TreeNode *root) {
    if(!root) {
        return;
    }
    if(root->left) {
        cal(root->left);
        root->val += root->left->val;
    }
    if(root->right) {
        cal(root->right);
        root->val += root->right->val;
    }
}

unordered_map<int, int> counts;
void number(TreeNode *root)
{
    if(!root) {
        return;
    }
    counts[root->val]++;
    if(root->left) {
        number(root->left);
    }
    if(root->right) {
        number(root->right);
    }
}

int main() {
    
    int N;
    cin >> N;
    vector<int> inbuff(2 * N + 1);
    for (int i = 0; i < 2 * N + 1; i++) {
        cin >> inbuff[i];
    }
    deque<TreeNode *> buff;
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
                curr->left = new TreeNode();
                curr->left->val = inbuff[inbuff_ind];
                buff.push_back(curr->left);
                curr_layer++;
            }
            inbuff_ind++;
            if(inbuff[inbuff_ind] != -1) {
                curr->right = new TreeNode();
                curr->right->val = inbuff[inbuff_ind];
                buff.push_back(curr->right);
                curr_layer++;
            }
            inbuff_ind++;
        }
        last_layer = curr_layer;
    }

    cal(head);

    number(head);

    int maxnum = 0;
    int maxcount = 0;

    for(auto pair: counts) {
        if(pair.second > maxcount) {
            maxnum = pair.first;
            maxcount = pair.second;
        }
    }

    cout << maxnum << " " << maxcount << endl;
}