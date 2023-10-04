#include <iostream>
#include <cassert>
using namespace std;

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

    size_t size(){
        return _size;
    }

    bool is_empty(){
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


int main(int, char**){
    //stack test
    int nums;       //number of tests
    int opr, ops;   //0 pop, 1 push
    LinkedStack<int> st;

    cin >> nums;
    for (int i = 0; i < nums; i++)
    {
        cin >> opr >> ops;
        if(opr) {
            st.push(ops);
        } else {
            st.pop();
        }
    }

    st.reverse_show();
}
