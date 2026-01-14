//
// Created by Michał Kasjaniuk on 14/01/2026.
//

#include <iostream>

using namespace std;


// węzeł
struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

// struktura stosu
struct Stack {
    Node* top;

    Stack() : top(nullptr) {}

    // Dodawnie elementu na górę
    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
        cout << "Wrzucono na stos: " << val << endl;
    }

    // Zdejmowanie z góry
    void pop() {
        if (top == nullptr) {
            cout << "Nie mozna stos" << endl;
            return;
        }
        Node* temp = top;
        top = top->next;
        delete temp;
        cout << "Usunieto ze stosu" << endl;
    }

    // podgladnie co na wierzchu
    void display_top() {
        if (top == nullptr) {
            cout << "Nie mozna stos" << endl;
        }
        else {
            cout << "Na gorze jest: " << top->data << endl;
        }
    }

    // czy jest cos
    bool isEmpty() {
        return top == nullptr;
    }
};

int main() {
    Stack mojStos;

    cout << mojStos.isEmpty() << endl;
    mojStos.push(10);
    mojStos.push(20);
    mojStos.push(30);
    mojStos.push(505);
    mojStos.display_top();

}