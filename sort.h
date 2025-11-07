#ifndef AISD_2_SORT_H
#define AISD_2_SORT_H

#include "array.h"

class Sort {
private:
    const int minRun = 64;
    bool isGalloping = false;
    const int minGallop = 7;
    int currentMinRun = 0;
    /*
    static const int initialStackSize = 40;
    int stackSize = 0;

    Run stack[initialStackSize]; // for storing run arrays */

    Array& array;

    int findMinRun(int arraySize);
    void insertionSort(int left, int right);
    void mergeSort(int left, int mid, int right);
    int leftGallop(int key, Array& array, int begin, int finish);
    int rightGallop(int key, Array& array, int begin, int finish);
public:
    Sort(Array& arr);

    void timSort();

    ~Sort() = default;
};

#endif //AISD_2_SORT_H