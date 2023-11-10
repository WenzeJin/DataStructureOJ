#include "ArrayDeque.h"

ArrayDeque::ArrayDeque() {
    _size = 0;
    _maxsize = 10;
    _head = 0;
    _tail = 1;
    _buffer = new int[_maxsize];
}

ArrayDeque::ArrayDeque(size_t size) {
    if(size == 0) {
        size = 1;
    }
    _size = 0;
    _maxsize = size + 1;
    _head = 0;
    _tail = 1;
    _buffer = new int[_maxsize];
}

int ArrayDeque::front() {
    return _buffer[_head];
}

int ArrayDeque::back() {
    return _buffer[_tail];
}

