#include <iostream>
#include <vector>

#define PRINT_PROC
#define PRINT_STAT

void printVector(std::vector<int> v) {
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i] << " ";
    }
    std::cout << std::endl;
}

void binaryInsertionSort(std::vector<int> &v) {
    size_t sz = v.size();
    int cnt = 0;
    int cmps = 0;
    while (cnt < sz) {
        int left = 0, right = cnt - 1;
        int mid = (left + right) / 2;
        int pivot = v[cnt];
        while (left <= right) {
            mid = (left + right) / 2;
            if (v[mid] > pivot) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
            cmps++;
        }
        for (int k = cnt - 1; k >= left; k--) {
            v[k + 1] = v[k];
        }
        v[left] = pivot;
        cnt++;

#ifdef PRINT_PROC
        std::cout << "Round " << cnt << ": ";
        printVector(v);
#endif
    }

#ifdef PRINT_STAT
    std::cout << "Total compare times: " << cmps << std::endl;
#endif

}

void shellSort(std::vector<int>& v) {
    size_t sz = v.size();
    int gap = sz - 0 + 1;
    int cmps = 0;
    do {
        gap = gap / 3 + 1;
        for (int left = 0; left < gap; left ++) {
            int cnt = 0;
            for (int i = left; i < sz; i += gap) {
                int pivot = v[i];
                int j = left;
                for (; j < i; j += gap) {
                    if(v[j] > v[i]) {
                        break;
                    }
                    cmps++;
                }

                for (int k = i - gap; k >= j; k -= gap) {
                    v[k + gap] = v[k];
                }

                v[j] = pivot;
                cnt++;

#ifdef PRINT_PROC
                std::cout << "Gap " << gap <<", Round " << cnt << ": ";
                printVector(v);
#endif
            }
        }
    } while (gap > 1);

#ifdef PRINT_STAT
    std::cout << "Total compare times: " << cmps << std::endl;
#endif

}

void printDivid() {
    std::cout << "====================================================" << std::endl;
}

int main() {
    std::vector<int> model = {21, 25, 49, 25, 16, 8};
    auto test = model;
    std::cout << "Test Array:" << std::endl;
    printVector(test);
    printDivid();

    std::cout << "BinaryInsertionSorted Array:" << std::endl;
    binaryInsertionSort(test);
    printVector(test);
    printDivid();

    test = model;
    std::cout << "ShellSorted Array:" << std::endl;
    shellSort(test);
    printVector(test);
    printDivid();
}