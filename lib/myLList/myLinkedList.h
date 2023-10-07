#ifndef MYLINKEDLIST
#define MYLINKEDLIST

#include <cassert>

//Double Linked List
template<typename T>
class myLinkedList {

    struct Node {
        T val;
        Node *prev;
        Node *next;
    };

    Node *head;
    size_t _size;

    //TODO: Iterator 类，用于降低遍历链表的时间复杂度。

    void delete_node(Node * pt) {
        //pt must be a node of this LinkedList
        //pt will be moved to the next element
        assert(_size > 0);
        if(pt->prev && pt->next) {
            pt->prev->next = pt->next;
            pt->next->prev = pt->prev;
            Node *temp = pt->next;
            delete pt;
            pt = temp;
            _size--;
        }
    }

public:

    myLinkedList() {
        head = new Node();
        head->prev = head;
        head->next = head;
        _size = 0;
    }

    ~myLinkedList() {
        Node *pt = head->next;
        while(pt != head){
            pt = pt->next;
            delete pt->prev;
        }
        delete head;
        head = nullptr;
        _size = 0;
    }

    T& operator[](int i){
        assert(i >= 0 && i < _size);
        Node *pt = head;
        if (i >= _size / 2) {
            int cnt = _size - 1;
            pt = pt->prev;
            while (cnt != i) {
                cnt--;
                pt = pt->prev;
            }
        } else {
            int cnt = 0;
            pt = pt->next;
            while (cnt != i) {
                cnt++;
                pt = pt->next;
            }
        }
        return pt->val;
    }

    void push_back(T& v) {
        Node *temp = new Node();
        temp->val = v;
        temp->prev = head->prev;
        temp->next = head;
        temp->prev->next = temp;
        head->perv = temp;
        _size++;
    }

    void push_front(T& v) {
        Node *temp = new Node();
        temp->val = v;
        temp->next = head->next;
        temp->perv = head;
        temp->next->prev = temp;
        head->next = temp;
        _size++;
    }

    void pop_back() {
        assert(_size > 0);
        Node *old = head->prev;
        head->prev = old->prev;
        old->prev->next = head;
        delete old;
        _size--;
    }

    void pop_front() {
        assert(_size > 0);
        Node *old = head->next;
        head->next = old->next;
        old->next->prev = head;
        delete old;
        _size--;
    }

    void insert_at(int i, T& v) {
        assert(i > 0 && i <= _size);
        Node *pt = head->next;
        int cnt = 0;
        while (cnt != i) {
            cnt++;
            pt = pt->next;
        }
        Node *temp = new Node();
        temp->val = v;
        temp->prev = pt->prev;
        pt->prev->next = temp;
        temp->next = pt;
        pt->prev = temp;
        _size++;
    }

    void delete_at(int i) {
        assert(i > 0 && i < _size); //_size also > 0
        Node *pt = head->next;
        int cnt = 0;
        while (cnt != i) {
            cnt++;
            pt = pt->next;
        }
        pt->prev->next = pt->next;
        pt->next->prev = pt->prev;
        delete pt;
        _size--;
    }

    void delete_for(T& v) {
        if (_size > 0) {
            Node *pt = head->next;
            while (pt != head) {
                if (pt->val == v && pt != head) {
                    delete_node(pt);
                    return;
                }
            }
        }
    }

    void delete_forall(T& v) {
        if (_size > 0) {
            Node *pt = head->next;
            while (pt != head && _size > 0) {
                if (pt->val == v && pt != head) {
                    delete_node(pt);
                }
            }
        }
    }

};

#endif