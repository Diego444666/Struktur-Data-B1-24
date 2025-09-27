#include <iostream>
#include <string>
#include <limits> 

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
    Node *prev; 
};

Node *head = nullptr;
Node *tail = nullptr;

void clearScreen();
void pauseScreen();
void displayHeader();
bool isInventoryEmpty();
void addItem(std::string nama, std::string tipe);
void insertItemAtPersonalizedPosition();
void deleteLastItem();
void deleteSpecificItem(Node* nodeToDelete);
void useItem();
void displayInventory();
void displayInventoryBackward();
void findItemDetail();


void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    std::cout << "\nTekan Enter untuk melanjutkan...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void displayHeader() {
    std::cout << "+=============================================================+" << std::endl;
    std::cout << "|              SISTEM MANAJEMEN INVENTARIS (DLL)              |" << std::endl;
    std::cout << "|                 " << NAMA << " - " << NIM << "                     |" << std::endl;
    std::cout << "+=============================================================+" << std::endl;
}

bool isInventoryEmpty() {
    return head == nullptr;
}

void addItem(std::string nama, std::string tipe) {
    Node *newNode = new Node();
    newNode->data.namaItem = nama;
    newNode->data.jumlah = JUMLAH_ITEM_AWAL;
    newNode->data.tipe = tipe;
    newNode->next = nullptr;
    newNode->prev = tail;

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
    if (POSISI_SISIP < 1) {
        std::cout << "\n--- Posisi sisip tidak valid (harus >= 1)." << std::endl;
        return;
    }

    std::string nama, tipe;
    std::cout << "\nMasukkan Nama Item yang akan disisipkan: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nama);
    std::cout << "Masukkan Tipe Item: ";
    std::getline(std::cin, tipe);

    Node *newNode = new Node();
    newNode->data.namaItem = nama;
    newNode->data.jumlah = JUMLAH_ITEM_AWAL;
    newNode->data.tipe = tipe;

    if (POSISI_SISIP == 1) { 
        newNode->next = head;
        newNode->prev = nullptr;
        if (head != nullptr) {
            head->prev = newNode;
        }
        head = newNode;
        if (tail == nullptr) {
            tail = newNode;
        }
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
            delete newNode; 
            addItem(nama, tipe);
        } else { 
            newNode->next = temp->next;
            newNode->prev = temp;
            if (temp->next != nullptr) {
                temp->next->prev = newNode;
            }
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

    Node* nodeToDelete = tail;
    if (head == tail) { 
        head = nullptr;
        tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    delete nodeToDelete;
    std::cout << "\n--- Item terakhir berhasil dihapus dari inventaris." << std::endl;
}


void deleteSpecificItem(Node* nodeToDelete) {
    if (isInventoryEmpty() || nodeToDelete == nullptr) {
        return;
    }

    if (nodeToDelete == head) {
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
    } else if (nodeToDelete == tail) { 
        tail = nodeToDelete->prev;
        tail->next = nullptr;
    } else { 
        nodeToDelete->prev->next = nodeToDelete->next;
        nodeToDelete->next->prev = nodeToDelete->prev;
    }
    delete nodeToDelete;
}

void useItem() {
    if (isInventoryEmpty()) {
        std::cout << "\n--- Inventaris kosong. Tidak ada item yang bisa digunakan." << std::endl;
        return;
    }

    std::string nama;
    std::cout << "\nMasukkan nama item yang ingin digunakan: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    std::cout << "\n+-------------------------------------+" << std::endl;
    std::cout << "|       DAFTAR INVENTARIS (DEPAN)     |" << std::endl;
    std::cout << "+-------------------------------------+" << std::endl;

    if (isInventoryEmpty()) {
        std::cout << "|         INVENTARIS KOSONG         |" << std::endl;
        std::cout << "+-------------------------------------+" << std::endl;
        return;
    }

    Node *temp = head;
    int i = 1;
    while (temp != nullptr) {
        std::cout << "| Item ke-" << i++ << std::endl;
        std::cout << "| Nama   : " << temp->data.namaItem << std::endl;
        std::cout << "| Jumlah : " << temp->data.jumlah << std::endl;
        std::cout << "| Tipe   : " << temp->data.tipe << std::endl;
        std::cout << "+-------------------------------------+" << std::endl;
        temp = temp->next;
    }
}

void displayInventoryBackward() {
    std::cout << "\n+-------------------------------------+" << std::endl;
    std::cout << "|      DAFTAR INVENTARIS (BELAKANG)   |" << std::endl;
    std::cout << "+-------------------------------------+" << std::endl;

    if (isInventoryEmpty()) {
        std::cout << "|         INVENTARIS KOSONG         |" << std::endl;
        std::cout << "+-------------------------------------+" << std::endl;
        return;
    }

    Node *temp = tail;
    int i = 1;
    while (temp != nullptr) {
        std::cout << "| Item ke-" << i++ << " (dari belakang)" << std::endl;
        std::cout << "| Nama   : " << temp->data.namaItem << std::endl;
        std::cout << "| Jumlah : " << temp->data.jumlah << std::endl;
        std::cout << "| Tipe   : " << temp->data.tipe << std::endl;
        std::cout << "+-------------------------------------+" << std::endl;
        temp = temp->prev;
    }
}

void findItemDetail() {
    if (isInventoryEmpty()) {
        std::cout << "\n--- Inventaris kosong. Tidak ada item yang bisa dicari." << std::endl;
        return;
    }

    std::string nama;
    std::cout << "\nMasukkan nama item yang ingin dicari: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, nama);

    Node *current = head;
    bool found = false;
    while (current != nullptr) {
        if (current->data.namaItem == nama) {
            std::cout << "\n+-------------------------------------+" << std::endl;
            std::cout << "|           DETAIL ITEM DITEMUKAN     |" << std::endl;
            std::cout << "+-------------------------------------+" << std::endl;
            std::cout << "| Nama   : " << current->data.namaItem << std::endl;
            std::cout << "| Jumlah : " << current->data.jumlah << std::endl;
            std::cout << "| Tipe   : " << current->data.tipe << std::endl;
            std::cout << "+-------------------------------------+" << std::endl;
            found = true;
            break;
        }
        current = current->next;
    }

    if (!found) {
        std::cout << "\n--- Item '" << nama << "' tidak ditemukan di inventaris." << std::endl;
    }
}


int main() {
    int choice;
    do {
        clearScreen();
        displayHeader();
        std::cout << "| [1] Tambah Item Baru                                        |" << std::endl;
        std::cout << "| [2] Sisipkan Item (di posisi " << POSISI_SISIP << ")                            |" << std::endl;
        std::cout << "| [3] Hapus Item Terakhir                                     |" << std::endl;
        std::cout << "| [4] Gunakan Item                                            |" << std::endl;
        std::cout << "| [5] Tampilkan Inventory (dari Depan)                        |" << std::endl;
        std::cout << "| [6] Tampilkan Inventory (dari Belakang)                     |" << std::endl;
        std::cout << "| [7] Cari Detail Item                                        |" << std::endl;
        std::cout << "| [0] Keluar                                                  |" << std::endl;
        std::cout << "+-------------------------------------------------------------+" << std::endl;
        std::cout << "Masukkan pilihan Anda: ";

        while (!(std::cin >> choice)) {
            std::cout << "Input tidak valid. Masukkan angka: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1: {
                std::string nama, tipe;
                std::cout << "\nMasukkan Nama Item: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, nama);
                std::cout << "Masukkan Tipe Item: ";
                std::getline(std::cin, tipe);
                addItem(nama, tipe);
                pauseScreen();
                break;
            }
            case 2:
                insertItemAtPersonalizedPosition();
                pauseScreen();
                break;
            case 3:
                deleteLastItem();
                pauseScreen();
                break;
            case 4:
                useItem();
                pauseScreen();
                break;
            case 5:
                displayInventory();
                pauseScreen();
                break;
            case 6:
                displayInventoryBackward();
                pauseScreen();
                break;
            case 7:
                findItemDetail();
                pauseScreen();
                break;
            case 0:
                std::cout << "\nTerima kasih, program diakhiri." << std::endl;
                break;
            default:
                std::cout << "\nPilihan tidak valid. Silakan coba lagi." << std::endl;
                pauseScreen();
                break;
        }
    } while (choice != 0);

    return 0;
}