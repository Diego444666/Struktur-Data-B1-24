#include <iostream>
#include <string>

const std::string NAMA = "Fachlevi Muhammad";
const std::string NIM = "059";
const int JUMLAH_ITEM_AWAL = 59; 
const int POSISI_SISIP = 10;     

struct Item {
    std::string namaItem;
    int jumlah;
    std::string tipe;
};

struct Node {
    Item data;
    Node *next;
};

Node *head = nullptr;
Node *tail = nullptr;

bool isInventoryEmpty() {
    return head == nullptr;
}

void addItem(std::string nama, std::string tipe) {
    Node *newNode = new Node();
    newNode->data.namaItem = nama;
    newNode->data.jumlah = JUMLAH_ITEM_AWAL;
    newNode->data.tipe = tipe;
    newNode->next = nullptr;

    if (isInventoryEmpty()) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    std::cout << "\n--- Item '" << nama << "' berhasil ditambahkan ke inventaris." << std::endl;
}

void insertItemAtPersonalizedPosition() {
    std::string nama, tipe;
    std::cout << "\nMasukkan Nama Item yang akan disisipkan: ";
    std::cin.ignore();
    std::getline(std::cin, nama);
    std::cout << "Masukkan Tipe Item: ";
    std::getline(std::cin, tipe);

    Node *newNode = new Node();
    newNode->data.namaItem = nama;
    newNode->data.jumlah = JUMLAH_ITEM_AWAL;
    newNode->data.tipe = tipe;

    if (POSISI_SISIP == 1) { 
        newNode->next = head;
        head = newNode;
        std::cout << "\n--- Item '" << nama << "' berhasil disisipkan di posisi awal." << std::endl;
    } else {
        Node *temp = head;
        int currentPosition = 1;
        while (temp != nullptr && currentPosition < POSISI_SISIP - 1) {
            temp = temp->next;
            currentPosition++;
        }

        if (temp == nullptr) {
            std::cout << "\n--- Posisi tidak valid. Menambahkan item di akhir." << std::endl;
            addItem(nama, tipe);
            delete newNode; 
        } else {
            newNode->next = temp->next;
            temp->next = newNode;
            if (newNode->next == nullptr) { 
                tail = newNode;
            }
            std::cout << "\n--- Item '" << nama << "' berhasil disisipkan di posisi " << POSISI_SISIP << "." << std::endl;
        }
    }
}

void deleteLastItem() {
    if (isInventoryEmpty()) {
        std::cout << "\n--- Inventaris kosong. Tidak ada yang bisa dihapus." << std::endl;
        return;
    }

    if (head == tail) { 
        delete head;
        head = nullptr;
        tail = nullptr;
    } else {
        Node *temp = head;
        while (temp->next != tail) {
            temp = temp->next;
        }
        delete tail;
        tail = temp;
        tail->next = nullptr;
    }
    std::cout << "\n--- Item terakhir berhasil dihapus dari inventaris." << std::endl;
}

void deleteSpecificItem(Node *nodeToDelete) {
    if (isInventoryEmpty() || nodeToDelete == nullptr) {
        return;
    }

    if (nodeToDelete == head) {
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete nodeToDelete;
        return;
    }

    Node *temp = head;
    while (temp->next != nullptr && temp->next != nodeToDelete) {
        temp = temp->next;
    }

    if (temp->next != nullptr) {
        if (nodeToDelete == tail) {
            tail = temp;
        }
        temp->next = nodeToDelete->next;
        delete nodeToDelete;
    }
}

void useItem() {
    if (isInventoryEmpty()) {
        std::cout << "\n--- Inventaris kosong. Tidak ada item yang bisa digunakan." << std::endl;
        return;
    }

    std::string nama;
    std::cout << "\nMasukkan nama item yang ingin digunakan: ";
    std::cin.ignore();
    std::getline(std::cin, nama);

    Node *current = head;
    while (current != nullptr) {
        if (current->data.namaItem == nama) {
            current->data.jumlah--;
            std::cout << "\n--- Item '" << nama << "' berhasil digunakan! Jumlah saat ini: " << current->data.jumlah << std::endl;

            if (current->data.jumlah <= 0) {
                std::cout << "--- Jumlah item habis. Item '" << nama << "' akan dihapus dari inventaris." << std::endl;
                deleteSpecificItem(current);
            }
            return;
        }
        current = current->next;
    }

    std::cout << "\n--- Item '" << nama << "' tidak ditemukan di inventaris." << std::endl;
}

void displayInventory() {
    if (isInventoryEmpty()) {
        std::cout << "\n-------------------------------------" << std::endl;
        std::cout << "|         INVENTARIS KOSONG         |" << std::endl;
        std::cout << "-------------------------------------" << std::endl;
        return;
    }

    std::cout << "\n-------------------------------------" << std::endl;
    std::cout << "|          DAFTAR INVENTARIS        |" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    
    Node *temp = head;
    while (temp != nullptr) {
        std::cout << "Nama: " << temp->data.namaItem << std::endl;
        std::cout << "Jumlah: " << temp->data.jumlah << std::endl;
        std::cout << "Tipe: " << temp->data.tipe << std::endl;
        std::cout << "-------------------------------------" << std::endl;
        temp = temp->next;
    }
}

int main() {
    int choice;
    do {
        std::cout << "\n+-------------------------------------------------------------+" << std::endl;
        std::cout << "|                 SISTEM MANAJEMEN INVENTARIS                 |" << std::endl;
        std::cout << "|          " << NAMA << " - " << NIM << "                            |" << std::endl;
        std::cout << "+-------------------------------------------------------------+" << std::endl;
        std::cout << "| 1. Tambah Item Baru                                         |" << std::endl;
        std::cout << "| 2. Sisipkan Item                                            |" << std::endl;
        std::cout << "| 3. Hapus Item Terakhir                                      |" << std::endl;
        std::cout << "| 4. Gunakan Item                                             |" << std::endl;
        std::cout << "| 5. Tampilkan Inventory                                      |" << std::endl;
        std::cout << "| 0. Keluar                                                   |" << std::endl;
        std::cout << "+-------------------------------------------------------------+" << std::endl;
        std::cout << "Masukkan pilihan Anda: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string nama, tipe;
                std::cout << "\nMasukkan Nama Item: ";
                std::cin.ignore();
                std::getline(std::cin, nama);
                std::cout << "Masukkan Tipe Item: ";
                std::getline(std::cin, tipe);
                addItem(nama, tipe);
                break;
            }
            case 2:
                insertItemAtPersonalizedPosition();
                break;
            case 3:
                deleteLastItem();
                break;
            case 4:
                useItem();
                break;
            case 5:
                displayInventory();
                break;
            case 0:
                std::cout << "\nTerima kasih, program diakhiri." << std::endl;
                break;
            default:
                std::cout << "\nPilihan tidak valid. Silakan coba lagi." << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}