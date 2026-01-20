#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left;
    Node *middle;
    Node *right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), middle(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};


Node* HUFFMAN(const map<char, int>& C) {
    int n = C.size();

    priority_queue<Node*, vector<Node*>, Compare> Q;

    for (auto const& [key, val] : C) {
        Q.push(new Node(key, val));
    }

    if (Q.size() % 2 == 0) {
        Q.push(new Node('\0', 0));
        n++;
    }

    while (Q.size() > 1) {
        Node* z = new Node('\0', 0);
        Node* x = Q.top(); Q.pop();
        z->left = x;
        Node* y = Q.top(); Q.pop();
        z->middle = y;
        Node* w = Q.top(); Q.pop();
        z->right = w;
        z->freq = x->freq + y->freq + w->freq;
        Q.push(z);

    }
    return Q.top();
}


void printCodes(Node* root, string code) {
    if (!root) return;

    if (!root->left && !root->middle && !root->right) {
        if (root->ch != '\0') {
            cout << root->ch << ": " << code << endl;
        }
        return;
    }

    printCodes(root->left, code + "0");
    printCodes(root->middle, code + "1");
    printCodes(root->right, code + "2");
}

int main() {
    map<char, int> C = {
        {'a', 45}, {'b', 13}, {'c', 12},
        {'d', 16}, {'e', 9},  {'f', 5}
    };
    cout << "Budowanie drzewa..." << endl;
    Node* root = HUFFMAN(C);
    cout << "Kody Ternarne (0, 1, 2):" << endl;
    printCodes(root, "");

    return 0;
}