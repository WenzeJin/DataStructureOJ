#ifndef ARRAY_DEQUEUE
#define ARRAY_DEQUEUE

#include <cstddef>

class ArrayDeque {

    int * _buffer;
    size_t _size;
    size_t _head;
    size_t _tail;
    size_t _maxsize;

public:
    ArrayDeque();
    ArrayDeque(size_t size);
    void push_back(int item);
    void push_front(int item);
    int front();
    int back();
    int pop_front();
    int pop_back();
    size_t size();
    bool empty();
    int operator[](size_t index);

private:
    void extend();
};

#endif