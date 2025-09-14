#include <iostream>

int main() {
    const int SIZE = 3;
    int matrix[SIZE][SIZE];

    int count = 1;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            matrix[i][j] = count++;
        }
    }

    std::cout << "Matriks 3x3:" << std::endl;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    int main_diag_sum = 0;
    int sec_diag_sum = 0;

    for (int i = 0; i < SIZE; ++i) {
        main_diag_sum += matrix[i][i];
        sec_diag_sum += matrix[i][SIZE - 1 - i];
    }

    std::cout << "Jumlah diagonal utama: " << main_diag_sum << std::endl;
    std::cout << "Jumlah diagonal sekunder: " << sec_diag_sum << std::endl;
    std::cout << "Total jumlah kedua diagonal: " << main_diag_sum + sec_diag_sum << std::endl;

    return 0;
}