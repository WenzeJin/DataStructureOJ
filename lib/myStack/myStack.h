
#ifndef MYSTACK
#define MYSTACK
#include <cassert>
#include <iostream>

template<typename T>
class ArrayStack {

    T *buffer;
    size_t _size;
    size_t _max_size;
    size_t _top;

private:

    void extend(){
        if(_max_size == 0) {
            //a new array will be created here
            _max_size = 10;
            if(buffer){
                delete[] buffer;
            }
            buffer = new T[10];
            _size = 0;
            _top = -1;
        } else { 
            T *old = buffer;
            _max_size *= 2;
            buffer = new T[_max_size];
            for (int i = 0; i < _size; i++)
            {
                buffer[i] = old[i];
            }
            //delete[] old;
        }
    }

public:

    ArrayStack(){
        buffer = new T[10];
        _size = 0;
        _max_size = 10;
        _top = -1;
    }

    ArrayStack(size_t size){
        assert(size > 0);
        _max_size = size;
        buffer = new T[size];
        _size = 0;
        _top = -1;
    }

    ~ArrayStack(){
        delete[] buffer;
        buffer = nullptr;
        _size = 0;
        _max_size = 0;
        _top = -1;
    }

    void push(T& obj){
        if(_size == _max_size){
            extend();
        }
        _top++;
        _size++;
        buffer[_top] = obj; // insert item
    }

    void pop(){
        assert(_size > 0);
        _size--;
        _top--;
    }

    T top(){
        assert(_size > 0);
        return buffer[_top];
    }

    size_t size(){
        return _size;
    }
    
    bool is_empty(){
        return _size == 0;
    }

    void show(){
        for (int i = 0; i < _size; i++){
            std::cout << buffer[i] << " ";
        }
        std::cout << std::endl;
    }
};

template<typename T>
class LinkedStack {
};

#endif