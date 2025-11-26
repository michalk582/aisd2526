#include <iostream>
#include <vector>

using namespace std;


void COUNTING_SORT(vector<int>& A, int d, long long exp) {
    int n = A.size();

    vector<int> C(d, 0);

    vector<int> B(n);

    for (int i = 0; i < n; i++) {
        int key = (A[i] / exp) % d;
        C[key] = C[key] + 1;
    }

    for (int j = 1; j < d; j++) {
        C[j] = C[j - 1] + C[j];
    }

    for (int i = n - 1; i >= 0; i--) {
        int key = (A[i] / exp) % d;

        B[C[key] - 1] = A[i];

        C[key] = C[key] - 1;
    }

    for (int i = 0; i < n; i++) {
        A[i] = B[i];
    }
}


void RADIX_SORT(vector<int>& A, int d, int k) {
    long long exp = 1;
    for (int i = 1; i <= k; i++) {
        COUNTING_SORT(A, d, exp);
        exp *= d;
    }
}



// Ujemne
void RADIX_SORT_W_NEG(vector<int>& A, int d, int k) {
    if (A.empty()) return;

    int minVal = A[0];
    for (int i = 1; i < A.size(); i++) {
        if (A[i] < minVal) {
            minVal = A[i];
        }
    }

    for (int i = 0; i < A.size(); i++) {
        A[i] = A[i] - minVal;
    }


    RADIX_SORT(A, d, k);


    for (int i = 0; i < A.size(); i++) {
        A[i] = A[i] + minVal;
    }
}


// int main() {
//     vector<int> A = {112, 111, 222, 222, 334 , 555, 552, 223, 999, 100};
//     vector<int> B = {-111, 222, 111, 222, 441, 241, 415, 555, 552, 223, -999, -100};
//     RADIX_SORT(A, 10, 3);
//     RADIX_SORT_W_NEG(B, 10, 4);
//     for (int i = 0; i < A.size(); i++) cout << A[i] << " ";
//     cout << endl;
//     for (int i = 0; i < B.size(); i++) cout << B[i] << " ";
//
// }
