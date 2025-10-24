#ifndef AISD_2_SORT_H
#define AISD_2_SORT_H

#include "array.h"

class Sort {
private:
    struct Run {
        int base;
        int length;
        Run() = default;
        Run(int initialBase, int initialLength) : base(initialBase), length(initialLength) {}
    };
    const int minRun = 32;
    const int minGallop = 7;
    static const int initialStackSize = 40;
    int stackSize = 0;
    int currentMinRun = 0;

    Run stack[initialStackSize]; // for storing run arrays

    Array& array;

    int findMinRun(int arraySize);
    void insertionSort(int left, int right);
    void mergeSort(int left, int mid, int right);
    int gallop(int key, Array& array, int base, int length);
    int findRunEnd(int start, int sizeArray);
    void timSortAlgorithm();
    void push(int base, int length);
    void mergeStack(int mergePoint);
    void mergeCollapse();
public:
    Sort(Array& arr);

    void timSort();

    ~Sort() = default;
};

#endif //AISD_2_SORT_H