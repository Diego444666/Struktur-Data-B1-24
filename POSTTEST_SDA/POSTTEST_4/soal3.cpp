// SOAL 3
#include <iostream>
#include <string>
using namespace std;

struct Node {
    string document;
    Node* next;
};

void enqueue(Node*& front, Node*& rear, string document) {
    Node* newNode = new Node{document, nullptr};

    // Kalau antrian masih kosong
    if (front == nullptr) {
        front = newNode;
        rear = newNode;
    }
    else {
        // Sambungin antrian dari belakang
        rear->next = newNode;
        rear = newNode;
    }
}

string dequeue(Node*& front, Node*& rear) {
    if (front == nullptr) return "Antrian kosong";

    Node* temp = front;
    string docData = temp->document;

    front = front->next;

    // Ini penting: kalau antrian jadi kosong, rear juga harus null
    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    return docData;
}

void processAllDocuments(Node*& front, Node*& rear) {
    cout << "Memulai pemrosesan antrian printer:" << endl;
    
    // Proses satu per satu sampai antrian habis
    while (front != nullptr) {
        cout << "Memproses: " << dequeue(front, rear) << endl;
    }
}

int main() {
    Node* front = nullptr;
    Node* rear = nullptr;

    enqueue(front, rear, "Document1.pdf");
    enqueue(front, rear, "Report.docx");
    enqueue(front, rear, "Presentation.pptx");
    
    processAllDocuments(front, rear);

    return 0;
}