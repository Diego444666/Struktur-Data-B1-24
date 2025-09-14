#include <iostream>
#include <string>

struct Mahasiswa {
    std::string nama;
    std::string nim;
    double ipk;
};

int main() {
    const int NUM_MAHASISWA = 5;
    Mahasiswa students[NUM_MAHASISWA];

    for (int i = 0; i < NUM_MAHASISWA; ++i) {
        std::cout << "Masukkan data mahasiswa " << i + 1 << ":" << std::endl;
        std::cout << "Nama: ";
        std::cin.ignore();
        std::getline(std::cin, students[i].nama);
        std::cout << "NIM: ";
        std::cin >> students[i].nim;
        std::cout << "IPK: ";
        std::cin >> students[i].ipk;
    }

    int highest_ipk_index = 0;
    for (int i = 1; i < NUM_MAHASISWA; ++i) {
        if (students[i].ipk > students[highest_ipk_index].ipk) {
            highest_ipk_index = i;
        }
    }

    std::cout << "\nMahasiswa dengan IPK tertinggi:" << std::endl;
    std::cout << "Nama: " << students[highest_ipk_index].nama << std::endl;
    std::cout << "NIM: " << students[highest_ipk_index].nim << std::endl;
    std::cout << "IPK: " << students[highest_ipk_index].ipk << std::endl;

    return 0;
}