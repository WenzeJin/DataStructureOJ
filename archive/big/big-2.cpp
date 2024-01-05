/*
    DATA STRUCTURE: Program Assignment 2
    Created by 金文泽 221220028.
*/

#include <iostream>
#include <stdio.h>
#include <cassert>
#define LC(pos) 2 * pos
#define RC(pos) 2 * pos + 1
#define INV 0x80000000

using namespace std;

/*
    Min heap
*/
class MinHeap {
    int * buffer;
    size_t _size;
    size_t k;
    int shift(size_t pos)
    {
        int max = pos;
        int parent = buffer[pos];
        if(LC(pos) <= _size) {
            if (buffer[LC(pos)] != INV && buffer[LC(pos)] < buffer[max]) {
                max = LC(pos);
            }
            if(RC(pos) <= _size) {
                if (buffer[RC(pos)] != INV && buffer[RC(pos)] < buffer[max]) {
                    max = RC(pos);
                }
            }
        }
        if(max != pos) {
            buffer[pos] = buffer[max];
            buffer[max] = parent;
        }
        if(max == pos) {
            return 0;
        }
        if(max == LC(pos)) {
            return 1;
        }
        if(max == RC(pos)) {
            return 2;
        }
        return 0;
    }

public:
    MinHeap(size_t size, size_t k) {
        this->k = k;
        _size = 0;
        buffer = new int[size + 2];
        for (int i = 1; i <= _size; i++) {
            buffer[i] = INV;
        }
    }

    void push(long long val) {
        if(_size == k && val <= top()) {
            return;
        }
        _size++;
        buffer[_size] = val;
        int curr = _size / 2;
        while (curr >= 1) {
            shift(curr);
            curr = curr / 2;
        }

        while(_size > k) {
            pop();
        }
    }

    void pop() {
        buffer[1] = buffer[_size];
        _size--;
        int curr = 1;
        while(curr <= _size) {
            int direct = shift(curr);
            if(direct == 0) {
                break;
            } else if (direct == 1) {
                curr = LC(curr);
            } else if (direct == 2) {
                curr = RC(curr);
            }
        }
    }

    int top() {
        assert(_size);
        return buffer[1];
    }

    size_t getSize() {
        return _size;
    }
};

/*
    Max heap
*/
class MaxHeap {
    int * buffer;
    size_t _size;
    size_t k;
    int shift(size_t pos)
    {
        int max = pos;
        int parent = buffer[pos];
        if(LC(pos) <= _size) {
            if (buffer[LC(pos)] != INV && buffer[LC(pos)] > buffer[max]) {
                max = LC(pos);
            }
            if(RC(pos) <= _size) {
                if (buffer[RC(pos)] != INV && buffer[RC(pos)] > buffer[max]) {
                    max = RC(pos);
                }
            }
        }
        if(max != pos) {
            buffer[pos] = buffer[max];
            buffer[max] = parent;
        }
        if(max == pos) {
            return 0;
        }
        if(max == LC(pos)) {
            return 1;
        }
        if(max == RC(pos)) {
            return 2;
        }
        return 0;
    }

public:
    MaxHeap(size_t size, size_t k) {
        this->k = k;
        _size = 0;
        buffer = new int[size + 2];
        for (int i = 1; i <= _size; i++) {
            buffer[i] = INV;
        }
    }

    void push(long long val) {
        if(_size == k && val >= top()) {
            return;
        }
        _size++;
        buffer[_size] = val;
        int curr = _size / 2;
        while (curr >= 1) {
            shift(curr);
            curr = curr / 2;
        }

        while(_size > k) {
            pop();
        }
    }

    void pop() {
        buffer[1] = buffer[_size];
        _size--;
        int curr = 1;
        while(curr <= _size) {
            int direct = shift(curr);
            if(direct == 0) {
                break;
            } else if (direct == 1) {
                curr = LC(curr);
            } else if (direct == 2) {
                curr = RC(curr);
            }
        }
    }

    int top() {
        assert(_size);
        return buffer[1];
    }

    size_t getSize() {
        return _size;
    }
};

/*
    Do the ceil division
*/
int getDemand(int cnt, int M) {
    int k = cnt / M;
    if (cnt % M){
        k++;
    }
    return k;
}

/*
    In this case, we will create and maintain two heaps: a min heap and a max heap. 
    The min heap will store the largest cnt elements, where cnt means current position of the wanted element. 
    So the top of the min heap will be the element we want. 
    The max heap will store the rest elements. 
    When the size of the min heap is smaller than we want, we will pop elements from the max heap ans push them into the min heap.
*/
int main() {
    int M, N;
    cin >> M >> N;
    MinHeap minHeap(N + 1, N + 1);
    MaxHeap maxHeap(N + 1, N + 1);

    for (int i = 0; i < N; i++) {
        int tmp;
        scanf("%d", &tmp);                  //avoid using std::cin to save time
        if (minHeap.getSize() < getDemand(i + 1, M)) {
            maxHeap.push(tmp);
        } else {
            if (tmp < minHeap.top()) {
                maxHeap.push(tmp);
            } else {
                maxHeap.push(minHeap.top());
                minHeap.pop();
                minHeap.push(tmp);
            }
        }
        while (minHeap.getSize() < getDemand(i + 1, M)) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        }
        printf("%d ", minHeap.top());       //avoid using std::cout to save time
    }
    printf("\n");
    return 0;
}