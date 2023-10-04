
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
    struct Node {
        T val;
        Node *next;
    };

    Node *head;
    size_t _size;

public:
    
    LinkedStack() {
        head = new Node();
        _size = 0;
        head->next = nullptr;
    }

    ~LinkedStack() {
        Node *pt = head->next;
        while(head != nullptr) {
            delete head;
            head = pt;
            if(pt)
                pt = pt->next;
        }
        head = nullptr;
        _size = 0;
    }

    void push(T value){
        Node *temp = new Node();
        _size++;
        temp->val = value;
        temp->next = head->next;
        head->next = temp;
    }

    T top(){
        assert(_size > 0);
        return head->next->val;
    }

    void pop(){
        assert(_size > 0);
        Node *temp = head->next;
        head->next = temp->next;
        delete temp;
        _size--;
    }

    void size(){
        return _size;
    }

    void is_empty(){
        return _size == 0;
    }

    void reverse_show() {
        Node *pt = head->next;
        while(pt != nullptr){
            std::cout << pt->val << " ";
            pt = pt->next;
        }
        std::cout << std::endl;
    }
};

#endif