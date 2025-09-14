#include <iostream>

void reverseArray(int *arr, int size) {
    int start = 0;
    int end = size - 1;
    while (start < end) {
        int temp = *(arr + start);
        *(arr + start) = *(arr + end);
        *(arr + end) = temp;
        start++;
        end--;
    }
}

void printArray(int *arr, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << *(arr + i) << " ";
    }
    std::cout << std::endl;
}

int main() {
    const int SIZE = 7;
    int arr[SIZE];

    for (int i = 0; i < SIZE; ++i) {
        arr[i] = (i + 1) * 3;
    }

    std::cout << "Array sebelum dibalik:" << std::endl;
    printArray(arr, SIZE);

    reverseArray(arr, SIZE);

    std::cout << "Array sesudah dibalik:" << std::endl;
    printArray(arr, SIZE);

    return 0;
}