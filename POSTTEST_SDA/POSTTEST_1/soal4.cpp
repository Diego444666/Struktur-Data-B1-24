#include <iostream>

void swap(int **a, int **b) {
    int *temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10;
    int y = 20;

    int *ptr_x = &x;
    int *ptr_y = &y;

    std::cout << "Nilai sebelum pertukaran:" << std::endl;
    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;

    swap(&ptr_x, &ptr_y);

    std::cout << "\nNilai sesudah pertukaran (menggunakan variabel asli):" << std::endl;
    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;
    
    std::cout << "\nNilai sesudah pertukaran (menggunakan pointer yang sudah ditukar):" << std::endl;
    std::cout << "*ptr_x = " << *ptr_x << std::endl;
    std::cout << "*ptr_y = " << *ptr_y << std::endl;

    return 0;
}