// SOAL 2
#include <iostream>
#include <string>
using namespace std;

struct Node {
    char data;
    Node* next;
};

void push(Node*& top, char data) {
    Node* newNode = new Node{data, top};
    top = newNode;
}

char pop(Node*& top) {
    if (top == nullptr) return '\0';
    Node* temp = top;
    char poppedValue = temp->data;
    top = top->next;
    delete temp;
    return poppedValue;
}

bool areBracketsBalanced(string expr) {
    Node* stackTop = nullptr;

    for (char c : expr) {
        // Kalau kurung buka, simpen aja dulu
        if (c == '(' || c == '{' || c == '[') {
            push(stackTop, c);
        }
        // Kalau kurung tutup, kita cek pasangannya
        else if (c == ')' || c == '}' || c == ']') {
            if (stackTop == nullptr) return false;

            char topChar = pop(stackTop);
            
            // Periksa apakah kurung tutupnya cocok sama kurung buka terakhir
            if ((c == ')' && topChar != '(') ||
                (c == '}' && topChar != '{') ||
                (c == ']' && topChar != '[')) {
                return false;
            }
        }
    }

    // Kalau loop selesai, stack harusnya kosong. Kalau ada sisa, berarti ga seimbang.
    return stackTop == nullptr;
}

int main() {
    string expr1 = "{[()]}";
    cout << expr1 << " -> " << (areBracketsBalanced(expr1) ? "Seimbang" : "Tidak Seimbang") << endl;

    string expr2 = "{[(])}";
    cout << expr2 << " -> " << (areBracketsBalanced(expr2) ? "Seimbang" : "Tidak Seimbang") << endl;

    return 0;
}