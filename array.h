#ifndef AISD_2_ARRAY_H
#define AISD_2_ARRAY_H

class Array {
private:
    int size = 0;
    int capacity = 2;
    int *array = nullptr;
public:
    Array();
    Array(int initialCapacity);

    void resize();
    void add(int value);
    void addIndex(int index, int value);
    void remove(int index);
    int get(int index);
    void changeValue(int index, int newValue);
    void printArray();
    void reverseArray(int left, int right);

    int getSize() const;
    bool isEmpty() const;

    ~Array();
};

#endif //AISD_2_ARRAY_H