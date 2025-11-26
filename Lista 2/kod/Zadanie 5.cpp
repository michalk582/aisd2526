#include <iostream>
#include <vector>
#include <chrono>    // Do mierzenia czasu
#include <random>    // Do generowania liczb


using namespace std;
using namespace std::chrono;


void COUNTING_SORT_DIGIT(vector<int>& A, int d, long long exp) {
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
        COUNTING_SORT_DIGIT(A, d, exp);
        exp *= d;
    }
}

void RADIX_SORT_W_NEG(vector<int>& A, int d, int k) {
    if (A.empty()) return;

    int minVal = A[0];
    for(int i = 1; i < A.size(); i++) {
        if (A[i] < minVal) minVal = A[i];
    }

    for(int i = 0; i < A.size(); i++) {
        A[i] = A[i] - minVal;
    }

    RADIX_SORT(A, d, k);

    for(int i = 0; i < A.size(); i++) {
        A[i] = A[i] + minVal;
    }
}



void runTest(int n, int d, const vector<int>& originalData) {
    //dane
    vector<int> data = originalData;

    int minVal = data[0];
    int maxVal = data[0];
    for(int x : data) {
        if(x < minVal) minVal = x;
        if(x > maxVal) maxVal = x;
    }

    long long range = (long long)maxVal - minVal;

    int k = 0;
    if (range == 0) k = 1;
    else {
        while (range > 0) {
            range /= d;
            k++;
        }
    }

    k += 1;

    auto start = high_resolution_clock::now();

    RADIX_SORT_W_NEG(data, d, k);

    auto end = high_resolution_clock::now();
    double elapsed = duration_cast<milliseconds>(end - start).count();

    cout << "Podstawa d = " << d
         << "\t(k = " << k << ")\t-> Czas: "
         << elapsed << " ms" << endl;
}


int main() {

    const int N = 1000000;
    cout << "Generowanie " << N << " losowych liczb..." << endl;

    vector<int> data(N);
    srand(time(NULL));
    for(int i=0; i<N; i++) {
        data[i] = (rand() % 200000000) - 100000000;
    }


    runTest(N, 2, data);
    runTest(N, 10, data);
    runTest(N, 100, data);
    runTest(N, 256, data);
    runTest(N, 1024, data);

    return 0;
}