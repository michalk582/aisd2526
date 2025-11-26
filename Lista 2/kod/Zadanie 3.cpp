#include <iostream>

using namespace std;


struct Node {
    int val;
    Node* next;

    Node(int v) : val(v), next(nullptr) {}
};


void push(Node*& head, int val) {
    Node* newNode = new Node(val);
    newNode->next = head;
    head = newNode;
}

void printList(Node* head) {
    while (head != nullptr) {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << "null" << endl;
}


void insertionSort(Node*& head) {
    Node* sorted = nullptr;

    Node* current = head;

    while (current != nullptr) {
        Node* nextNode = current->next;

        if (sorted == nullptr || sorted->val >= current->val) {
            current->next = sorted;
            sorted = current;
        }

        else {
            Node* temp = sorted;
            while (temp->next != nullptr && temp->next->val < current->val) {
                temp = temp->next;
            }

            current->next = temp->next;
            temp->next = current;
        }

        current = nextNode;
    }

    head = sorted;
}

int main() {
    Node* head = nullptr;

    push(head, 30);
    push(head, 3);
    push(head, 4);
    push(head, 20);
    push(head, 5);
    push(head, 140);

    cout << "Lista przed sortowaniem: ";
    printList(head);

    insertionSort(head);

    cout << "Lista po sortowaniu:     ";
    printList(head);

    return 0;
}


