class AVLTree {

    struct AVLTreeNode {
        int val;
        AVLTreeNode *left;
        AVLTreeNode *right;
        AVLTreeNode *parent;
        int bf;
        AVLTreeNode(int val) : val(val), left(nullptr), right(nullptr), parent(nullptr), bf(0) {}
    };

    AVLTreeNode *head;
    unsigned _size;

    void rotateR(AVLTreeNode *&ptr) {
        AVLTreeNode *curr = ptr->left;
        ptr->left = curr->right;
        if(curr->right)
            curr->right->parent = ptr;
        curr->right = ptr;
        ptr->parent = curr;
        curr->bf = 0;
        ptr->bf = 0;
        if(head == ptr)
            head = curr;
        ptr = curr;
    }

    void rotateL(AVLTreeNode *&ptr) {
        AVLTreeNode *curr = ptr->right;
        ptr->right = curr->left;
        if(curr->left)
            curr->left->parent = ptr;
        curr->left = ptr;
        ptr->parent = curr;
        curr->bf = 0;
        ptr->bf = 0;
        if(head == ptr)
            head = curr;
        ptr = curr;
    }

    void rotateLR(AVLTreeNode *&ptr) {
        AVLTreeNode *subL = ptr->left;
        AVLTreeNode *subLR = subL->right;

        if(subLR->bf == 0) {
            subL->bf = 0;
            ptr->bf = 0;
            subLR->bf = 0;
        } else if(subLR->bf == 1) {
            subL->bf = -1;
            ptr->bf = 0;
            subLR->bf = 0;
        } else if(subLR->bf == -1) {
            subL->bf = 0;
            ptr->bf = 1;
            subLR->bf = 0;
        }

        subL->right = subLR->left;
        if(subLR->left)
            subLR->left->parent = subL;
        subLR->left = subL;
        subL->parent = subLR;
        ptr->left = subLR->right;
        if(subLR->right)
            subLR->right->parent = ptr;
        subLR->right = ptr;
        ptr->parent = subLR;
        if(head == ptr)
            head = subLR;
        ptr = subLR;
    }

    void rotateRL(AVLTreeNode *&ptr) {
        AVLTreeNode *subR = ptr->right;
        AVLTreeNode *subRL = subR->left;

        if(subRL->bf == 0) {
            ptr->bf = 0;
            subR->bf = 0;
            subRL->bf = 0;
        } else if(subRL->bf == 1) {
            subR->bf = 0;
            ptr->bf = -1;
            subRL->bf = 0;
        } else if(subRL->bf == -1) {
            subR->bf = 1;
            ptr->bf = 0;
            subRL->bf = 0;
        }

        subR->left = subRL->right;
        if(subRL->right)
            subRL->right->parent = subR;
        subRL->right = subR;
        subR->parent = subRL;
        ptr->right = subRL->left;
        if(subRL->left)
            subRL->left->parent = ptr;
        subRL->left = ptr;
        ptr->parent = subRL;
        if(head == ptr)
            head = subRL;
        ptr = subRL;
    }

public:
    AVLTree(): head(nullptr), _size(0){}

    void insert(int val) {
        if(_size == 0) {
            head = new AVLTreeNode(val);
        }
        else
        {
            AVLTreeNode *curr = head;
            while(1) {
                if(val < curr->val) {
                    if(curr->left) {
                        curr = curr->left;
                    } else {
                        curr->left = new AVLTreeNode(val);
                        curr->left->parent = curr;
                        curr = curr->left;
                        break;
                    }
                } else {
                    if(curr->right) {
                        curr = curr->right;
                    } else {
                        curr->right = new AVLTreeNode(val);
                        curr->right->parent = curr;
                        curr = curr->right;
                        break;
                    }
                }
            }
            AVLTreeNode *parent = curr->parent;
            while(parent) {
                if(curr == parent->right) {
                    parent->bf++;
                } else {
                    parent->bf--;
                }
                if(parent->bf == 0) {
                    //parent 高度不变，不影响平衡
                    break;
                } else if(parent->bf == 1 || parent->bf == -1) {
                    curr = parent;
                    parent = parent->parent;
                } else {
                    if(curr == parent->right) {
                        if(curr->bf == 1) 
                        {
                            rotateL(parent);
                        }
                        else
                        {
                            rotateRL(parent);
                        }
                    } else {
                        if(curr->bf == -1) 
                        {
                            rotateR(parent);
                        }
                        else
                        {
                            rotateLR(parent);
                        }
                    }
                }
            }
        }
        ++_size;
    }
};