// SOAL 1
#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* next;
};

// Nambahin data ke puncak stack
void push(Node*& top, char data) {
    Node* newNode = new Node{data, top};
    top = newNode;
}

// Ngambil data dari puncak stack
char pop(Node*& top) {
    if (top == nullptr) return '\0';
    Node* temp = top;
    char poppedValue = temp->data;
    top = top->next;
    delete temp;
    return poppedValue;
}

string reverseString(string s) {
    Node* stackTop = nullptr;
    string reversed = "";

    // 1. Masukin semua karakter ke stack
    for (char c : s) {
        push(stackTop, c);
    }

    // 2. Dikeluarin lagi dari stack, urutannya jadi kebalik secara alami
    while (stackTop != nullptr) {
        reversed += pop(stackTop);
    }

    return reversed;
}

int main() {
    string text = "Struktur Data";
    cout << "Teks asli: " << text << endl;
    cout << "Teks terbalik: " << reverseString(text) << endl;
    return 0;
}