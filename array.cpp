#include "array.h"
#include <iostream>

using namespace std;

Array::Array() {
    array = new int[capacity];
}

Array::Array(int initialCapacity) {
    if (capacity <= 0) {
        cout << "Incorect capacity. (Capacity < 0)";
        return;
    }

    this->capacity = initialCapacity;
    array = new int[capacity];
}

void Array::resize() {
    capacity *= 2;

    int* newArray = new int[capacity];

    for (int i = 0; i < size; i++) {
        newArray[i] = array[i];
    }

    delete[] array;
    array = newArray;
}

void Array::add(int value) {
    if (size >= capacity) {
        resize();
    }

    array[size] = value;
    size++;
}

void Array::addIndex(int value, int index) {
    if (index < 0 || index > size) {
        cout << "Incorrect index.";
    }

    if (size >= capacity) {
        resize();
    }

    for (int i = size; i > index; i--) {
        array[i] = array[i - 1];
    }

    array[index] = value;
    size++;
}

void Array::remove(int index) {
    if (index < 0 || index > size) {
        cout << "Incorrect index.";
    }

    for (int i = index; i < size - 1; i++) {
        array[i] = array[i + 1];
    }

    size--;
}

int Array::get(int index) {
    return array[index];
}

void Array::changeValue(int index, int newValue) {
    array[index] = newValue;
}

void Array::printArray() {
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
}

void Array::reverseArray(int left, int right) {
    while (left < right) {
        swap(left, right);
        ++left;
        --right;
    }
}

int Array::getSize() const {
    return size;
}

bool Array::isEmpty() const {
    return size == 0;
}



Array::~Array() {
    delete[] array;
    array = nullptr;
}


