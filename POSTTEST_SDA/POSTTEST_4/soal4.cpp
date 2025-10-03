// SOAL 4
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void sortedInsert(Node *&head_ref, int data) {
    Node* newNode = new Node{data, nullptr, nullptr};

    if (head_ref == nullptr) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }

    // Kasus: angka baru lebih kecil dari head, jadi head baru
    if (data <= head_ref->data) {
        Node* tail = head_ref->prev; // cari buntutnya dulu
        
        newNode->next = head_ref;
        head_ref->prev = newNode;
        newNode->prev = tail;
        tail->next = newNode;
        
        head_ref = newNode;
    }
    // Kasus: cari posisi di tengah atau akhir
    else {
        Node *current = head_ref;
        // Geser terus sampe nemu tempat yg pas
        while (current->next != head_ref && current->next->data < data) {
            current = current->next;
        }

        // Sisipkan node baru setelah 'current'
        newNode->next = current->next;
        current->next->prev = newNode;
        current->next = newNode;
        newNode->prev = current;
    }
}

void printList(Node *head_ref) {
    if (head_ref == nullptr) {
        cout << "List kosong" << endl;
        return;
    }
    Node *current = head_ref;
    do {
        cout << current->data << " ";
        current = current->next;
    } while (current != head_ref);
    cout << endl;
}

int main() {
    Node *head = nullptr;
    sortedInsert(head, 30);
    sortedInsert(head, 10);
    sortedInsert(head, 40);
    sortedInsert(head, 20);

    cout << "Circular Doubly Linked List (sorted): ";
    printList(head);

    return 0;
}