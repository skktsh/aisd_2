#include "sort.h"
#include <iostream>

using namespace std;

Sort::Sort(Array& arr) : array(arr) {};

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

int Sort::leftGallop(int key, Array &array, int begin, int finish) {
    int start = begin;
    int end = finish;

    while (start < end) {
        int mid = start + (end - start) / 2;

        if (array.get(mid) < key) {
            start = mid + 1;
        }

        else {
            end = mid;
        }
    }

    return start;
} //searching where to put the key value in the array by using binary search

int Sort::rightGallop(int key, Array &array, int begin, int finish) {
    int start = begin;
    int end = finish;

    while (start < end) {
        int mid = start + (end - start + 1) / 2;

        if (array.get(mid) <= key) {
            start = mid;
        }

        else {
            end = mid - 1;
        }
    }

    return start + 1;
}

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
    int leftWin = 0, rightWin = 0;

    while (i < lengthLeft && j < lengthRight) {
        if (leftArray.get(i) <= rightArray.get(j)) {
            array.changeValue(k++, leftArray.get(i++));
            if (isGalloping) {
                leftWin++;
                rightWin = 0;
            }
        }

        else {
            array.changeValue(k++, rightArray.get(j++));
            if (isGalloping) {
                rightWin++;
                leftWin = 0;
            }
        }

        if (!isGalloping) {
            if (leftWin >= minGallop || rightWin >= minGallop) {
                isGalloping = true;
            }
        }

        else {
            if (leftWin >= minGallop) {
                int newLengthLeft = 0;
                if (i < lengthLeft) {
                    newLengthLeft = rightGallop(rightArray.get(j-1), leftArray, i, lengthLeft - 1);
                    for (; i < newLengthLeft; i++) {
                        array.changeValue(k++, leftArray.get(i));
                    }
                }
                isGalloping = false;
                leftWin = 0;
            }

            if (rightWin >= minGallop) {
                int newLengthRight = 0;
                if (i < lengthRight) {
                    newLengthRight = leftGallop(leftArray.get(i - 1), rightArray, j, lengthRight - 1);
                    for (; j < newLengthRight; ++j) {
                        array.changeValue(k++, rightArray.get(j));
                    }
                }
                isGalloping = false;
                rightWin = 0;
            }
        }
    }

    while (i < lengthLeft) {
        array.changeValue(k++, leftArray.get(i++));
    }

    while (j < lengthRight) {
        array.changeValue(k++, rightArray.get(j++));
    }
}

void Sort::timSort() {
    if (array.isEmpty() || array.getSize() <= 1) {
        cout << "No actions with array are possible due to its size.";
        return;
    }

    int sizeArray = array.getSize();
    currentMinRun = findMinRun(sizeArray);

    for (int i = 0 ; i < sizeArray; i+=currentMinRun) {
        int right = (i + currentMinRun - 1) < (sizeArray - 1) ? i + currentMinRun - 1 : sizeArray - 1;
        insertionSort(i, right);
    }

    for (int j = currentMinRun; j < sizeArray; j = 2 * j) {
        for (int left = 0; left < sizeArray; left+= 2 * j) {
            int mid = left + j - 1;
            int right = (left + 2 * j - 1) < (sizeArray - 1) ? left + 2 * j - 1 : sizeArray - 1;

            if (mid < right && mid >= 0) {
                mergeSort(left, mid, right);
            }
        }
    }
}




