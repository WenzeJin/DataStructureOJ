#include <iostream>
#include <vector>
#include <deque>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int v): val(v), left(nullptr), right(nullptr) {}
};

int N;
vector<int> post;
vector<int> middle;

TreeNode *head;

void construct(TreeNode*& root, int ml, int mr, int pl, int pr) {
    if(ml > mr || pl > pr) {
        root = nullptr;
        return;
    }

    int curr = post[pl];

    int mid = ml;

    while(mid <= mr) {
        if(middle[mid] == curr) {
            break;
        }
        mid++;
    }

    int left_size = mid - ml;
    int right_size = mr - mid;

    root = new TreeNode(curr);

    construct(root->left, ml, mid - 1, pl + 1, pl + left_size);

    construct(root->right, mid + 1, mr, pl + left_size + 1, pr);
}

vector<int> ans;

int maxdepth = 0;

void left_vision(TreeNode *root, int depth) {
    if(depth > maxdepth) {
        ans.push_back(root->val);
        maxdepth = depth;
    }
    if(root->left)
        left_vision(root->left, depth + 1);
    if(root->right)
        left_vision(root->right, depth + 1);
}

int main()
{
    cin >> N;
    for (int i = 0; i < N; i++) {
        int temp;
        cin >> temp;
        post.push_back(temp);
    }

    for (int i = 0; i < N; i++) {
        int temp;
        cin >> temp;
        middle.push_back(temp);
    }

    construct(head, 0, N - 1, 0, N - 1);

    left_vision(head, 1);

    int asz = ans.size();

    for (int i = 0; i < asz; i++) {
        cout << ans[i] << " ";
    }

    cout << endl;
}