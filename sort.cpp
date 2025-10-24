#include "sort.h"
#include <iostream>

using namespace std;

Sort::Sort(Array& arr) : array(arr), stack{}, stackSize(0) {};

int Sort::findMinRun(int arraySize) {
    int run = 0;

    while (arraySize >= minRun) {
        run |= arraySize & 1;
        arraySize >>= 1;
    }

    return arraySize + run; //making sure that minRun is equal to or slightly less than a power of two
}

void Sort::insertionSort(int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int value = array.get(i);

        int j = i - 1;
        while (j >= left && array.get(j) > value) {
            array.changeValue(j + 1, array.get(j));
            j = j - 1;
        }

        array.changeValue(j + 1, value);
    }
}

int Sort::gallop(int key, Array &array, int base, int length) {
    int start = 0;
    int end = length;

    while (start < end) {
        int mid = (start + end) / 2;

        if (array.get(base + mid) < key) {
            start = mid + 1;
        }

        else {
            end = mid;
        }
    }

    return start;
} //searching where to put the key value in the array by using binary search


void Sort::mergeSort(int left, int mid, int right) {
    int lengthLeft = mid - left + 1;
    int lengthRight = right - mid;

    Array leftArray(lengthLeft);
    Array rightArray(lengthRight);
    for (int i = 0; i < lengthLeft; i++) {
        leftArray.changeValue(i, array.get(left + i));
    }

    for (int i = 0; i < lengthRight; i++) {
        rightArray.changeValue(i, array.get(mid  + 1 + i));
    }

    int i = 0, j = 0, k = left;
    const int minGallop = 7;
    int leftWin = 0, rightWin = 0;

    while (i < lengthLeft && j < lengthRight) {
        if (leftArray.get(i) <= rightArray.get(j)) {
            array.changeValue(k, leftArray.get(i));
            i++;
            leftWin++;
            rightWin = 0;
        }

        else {
            array.changeValue(k, rightArray.get(j));
            j++;
            rightWin++;
            leftWin = 0;
        }
        k++;

        if (leftWin >= minGallop || rightWin >= minGallop) {
            if (k > left) {
                i--;
                j--;
                k--;
            }

            if (j < lengthRight) {
                int gallopValueLeft = gallop(rightArray.get(j), leftArray, i, lengthLeft - i);

                for (int x = 0; x < gallopValueLeft && i < lengthLeft; ++x) {
                    array.changeValue(k++, leftArray.get(i++));
                }
            }

            if (i < lengthLeft) {
                int gallopValueRight = gallop(leftArray.get(i), rightArray, j, lengthRight - j);

                for (int x = 0; x < gallopValueRight && j < lengthRight; ++x) {
                    array.changeValue(k++, rightArray.get(j++));
                }
            }

            leftWin = 0;
            rightWin = 0;
        }
    }

    while (i < lengthLeft) {
        array.changeValue(k, leftArray.get(i));
        k++;
        i++;
    }

    while (j < lengthRight) {
        array.changeValue(k, rightArray.get(j));
        k++;
        j++;
    }
}

void Sort::timSort() {
    if (array.isEmpty() || array.getSize() <= 1) {
        cout << "No actions with array are possible due to its size.";
        return;
    }

    int sizeArray = array.getSize();

    if (sizeArray <= minRun) {
        insertionSort(0, sizeArray - 1);
        return;
    }
    timSortAlgorithm();
}

int Sort::findRunEnd(int start, int sizeArray) {
    int end  = start + 2;

    // check that some part of the array is already sorted
    if (array.get(start) > array.get(start + 1)) {
        while (end < sizeArray && array.get(end - 1) >= array.get(end)) {
            end++;
        }
        array.reverseArray(start, end - 1);
    }

    else {
        while (end < sizeArray && array.get(end - 1) <= array.get(end)) {
            end++;
        }
    }

    return end;
}

void Sort::push(int base, int length) {
    if (stackSize >= initialStackSize) {
        cout << "Stack is full." << std::endl;
    }

    stack[stackSize] = Run(base, length);
}

void Sort::mergeStack(int mergePoint) {
    Run& run1 = stack[mergePoint];
    Run& run2 = stack[mergePoint + 1];

    int fullLength = run1.length + run2.length;
    stackSize--;

    for (int j = mergePoint + 1; j < stackSize; j++ ) {
        stack[j] = stack[j + 1];
    }

    mergeSort(run1.base, run1.base + fullLength - run2.base - 1, run1.base + fullLength - run2.base - 1);
}

void Sort::mergeCollapse() {
    while (stackSize >= 1) {
        int n = stackSize - 2;

        if (n > 0 && stack[n - 1].length <= stack[n].length + stack[n + 1].length) {
            if (stack[n-1].length < stack[n + 1].length) {
                n--;
            }
            mergeStack(n);
        }

        else if (stack[n].length <= stack[n + 1].length) {
            mergeStack(n);
        }

        else {
            break;
        }
    }
}

void Sort::timSortAlgorithm() {
    int sizeArray = array.getSize();
    currentMinRun = findMinRun(sizeArray);

    int runBegin = 0;

    while (runBegin < sizeArray) {
        int runEnd = findRunEnd(runBegin, sizeArray);
        int runLength = runEnd - runBegin;

        if (runLength < minRun) {
            int minChoice = min(minRun, sizeArray - runBegin); // in case sizeArray is < minRun
            insertionSort(runBegin, minChoice + runBegin - 1);
            runLength = minChoice;
        }

        push(runBegin, runLength);
        mergeCollapse();
        runBegin += runLength;
    }

    while (stackSize > 1) {
        mergeStack(stackSize - 2);
    }
}


