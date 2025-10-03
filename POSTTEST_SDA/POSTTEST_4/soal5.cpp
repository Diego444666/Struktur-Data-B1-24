// SOAL 5
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev;
};

void exchangeHeadAndTail(Node *&head_ref) {
    // Ga bisa dituker kalau nodenya kurang dari 2
    if (head_ref == nullptr || head_ref->next == head_ref) {
        return;
    }

    Node* oldHead = head_ref;
    Node* oldTail = head_ref->prev;
    Node* headNext = oldHead->next;
    Node* tailPrev = oldTail->prev;

    // Kasus simpel kalau cuma ada 2 node, tinggal tukar headnya
    if (headNext == oldTail) {
        head_ref = oldTail;
        return;
    }

    // Inti dari penukaran: menyambungkan kembali tetangga dari head dan tail
    tailPrev->next = oldHead;
    oldHead->prev = tailPrev;

    headNext->prev = oldTail;
    oldTail->next = headNext;
    
    // Jadikan tail yang lama sebagai head yang baru
    head_ref = oldTail;
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

void insertEnd(Node *&head_ref, int data) {
    Node *newNode = new Node{data, nullptr, nullptr};
    if (head_ref == nullptr) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head_ref = newNode;
        return;
    }
    Node *tail = head_ref->prev;
    newNode->next = head_ref;
    newNode->prev = tail;
    head_ref->prev = newNode;
    tail->next = newNode;
}

int main() {
    Node *head = nullptr;
    insertEnd(head, 1);
    insertEnd(head, 2);
    insertEnd(head, 3);
    insertEnd(head, 4);
    insertEnd(head, 5);

    cout << "List sebelum exchange: ";
    printList(head);

    exchangeHeadAndTail(head);

    cout << "List setelah exchange head dan tail: ";
    printList(head);

    return 0;
}