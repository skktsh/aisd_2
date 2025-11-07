#include <chrono>
#include <iostream>

#include "array.h"
#include "sort.h"

using namespace std;
const int run = 64;

void showMenu() {
    cout << "1. Create an array and sort it. " << endl;
    cout << "2. Exit." << endl;
}

void arrayMenu() {
    cout << "1. Generate random numbers;" << endl;
    cout << "2. Enter numbers. " << endl;
}

int main() {
    Array array = Array();
    int size;

    while (true) {
        showMenu();

        int choice;
        cout << "Choose an option: " << endl;
        cin >> choice;

        if (choice == 1) {
            arrayMenu();
            int choiceArray;
            cout << "Choose an option: " << endl;
            cin >> choiceArray;


            if (choiceArray == 1) {
                cout << "Enter size of the array: ";
                cin >> size;
                for (int i = 0; i < size; i++) {
                    int value = rand() % 199 - 99;
                    array.add(value);
                }

                array.printArray();
                cout << endl;

                Sort arraySort(array);
                auto start = chrono::high_resolution_clock::now();
                arraySort.timSort();
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);

                cout << "The Sorted Array: " << endl;
                array.printArray();
                cout << endl;

                cout << "The time it took to sort the array is " << duration.count() << " ns" << endl;
            }

            if (choiceArray == 2) {
                cout << "Enter elements of the array (end with -1): ";
                int value;

                while (cin >> value && value != -1) {
                    array.add(value);
                }

                cout << endl;
                cout << "The array: " << endl;
                array.printArray();
                cout << endl;

                Sort arraySort(array);
                auto start = chrono::high_resolution_clock::now();
                arraySort.timSort();
                auto end = chrono::high_resolution_clock::now();
                auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);

                cout << "The Sorted Array: " << endl;
                array.printArray();
                cout << endl;

                cout << "The time it took to sort the array is " << duration.count() << " ns" << endl;
            }
        }
        else if (choice == 2) {
            return 0;
        }
        else {
            cout << "Incorrect choice number." << endl;
        }
    }
}