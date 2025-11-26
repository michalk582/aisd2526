#include <iostream>
#include <vector>

using namespace std;


void INSERTION_SORT(vector<float>& bucket) {
    int n = bucket.size();
    for (int i = 1; i < n; i++) {
        float key = bucket[i];
        int j = i - 1;

        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}


void BucketSort(vector<float>& A) {
    int n = A.size();
    vector<vector<float>> b(n);

    for (int i = 0; i < n; i++) {
        int bi = n * A[i];

        if (bi >= n) bi = n - 1;

        b[bi].push_back(A[i]);
    }

    for (int i = 0; i < n; i++) {
        INSERTION_SORT(b[i]);
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < b[i].size(); j++) {
            A[index++] = b[i][j];
        }
    }
}


void BucketSort_Modfied(vector<float>& A) {
    int n = A.size();
    if (n <= 1) return;

    float minVal = A[0];
    float maxVal = A[0];
    for (float x : A) {
        if (x < minVal) minVal = x;
        if (x > maxVal) maxVal = x;
    }
    float range = maxVal - minVal;
    if (range == 0) return;
    vector<vector<float>> B(n);


    for (int i = 0; i < n; i++) {
        int index = (int)((A[i] - minVal) / range * n);

        if (index >= n) {
            index = n - 1;
        }

        B[index].push_back(A[i]);
    }

    for (int j = 0; j < n; j++) {

        if (!B[j].empty()) {
            INSERTION_SORT(B[j]);
        }
    }

    int k = 0;
    for (int j = 0; j < n; j++) {
        for (float val : B[j]) {
            A[k++] = val;
        }
    }
}


// int main() {
//     vector<float> A = {0.12, 0.33, 0.14, 0.95, 0.96, 0.67, 0.22, 0.19, 0.20};
//     vector<float> B = {12, 41, 41, 51, 124, 41, 52, 41,245, 412, 21, 1};
//
//     // Wywołanie jest teraz prostsze, nie trzeba podawać rozmiaru
//     BucketSort(A);
//
//     for(int i = 0; i < A.size(); i++) {
//         cout << A[i] << " ";
//     }
//     cout << endl;
//     BucketSort_Modfied(B);
//
//     for(int i = 0; i < B.size(); i++) {
//         cout << B[i] << " ";
//     }
//
//     return 0;
// }