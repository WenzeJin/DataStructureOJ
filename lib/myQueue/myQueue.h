#ifndef MYQUEUE
#define MYQUEUE
#include <cassert>

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

    void push_front(T v) {
        Node *temp = new Node();
        temp->val = v;
        temp->prev = head;
        temp->next = head->next;
        head->next = temp;
        temp->next->prev = temp;
        _size++;
    }

    void push_back(T v) {
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

#endif