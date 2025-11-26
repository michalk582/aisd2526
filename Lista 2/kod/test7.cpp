//
// Created by Michał Kasjaniuk on 26/11/2025.
//


#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>
#include <cmath> // Dla pow()

using namespace std;
using namespace std::chrono;

// ==========================================
// 1. QUICK SORT (Standard)
// ==========================================

int PARTITION(vector<float>& A, int poczatek, int koniec) {
    float pivot = A[koniec];
    int i = poczatek - 1;

    for (int j = poczatek; j < koniec; j++) {
        if (A[j] <= pivot) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[koniec]);
    return i + 1;
}

void QUICK_SORT(vector<float>& A, int p, int k) {
    if (p < k) {
        int s = PARTITION(A, p, k);
        QUICK_SORT(A, p, s - 1);
        QUICK_SORT(A, s + 1, k);
    }
}

// ==========================================
// 2. QUICK SORT DUAL PIVOT
// ==========================================

void PARTITION_DUAL(vector<float>& A, int p, int k, int& lp, int& rp) {
    if (A[p] > A[k]) {
        swap(A[p], A[k]);
    }

    float pivot1 = A[p];
    float pivot2 = A[k];

    int i = p + 1;
    int gt = k - 1;
    int j = p + 1;

    while (j <= gt) {
        if (A[j] < pivot1) {
            swap(A[j], A[i]);
            i++;
            j++;
        }
        else if (A[j] > pivot2) {
            swap(A[j], A[gt]);
            gt--;
        }
        else {
            j++;
        }
    }

    i--;
    gt++;
    swap(A[p], A[i]);
    swap(A[k], A[gt]);

    lp = i;
    rp = gt;
}

void QUICK_SORT_DUAL(vector<float>& A, int p, int k) {
    if (p < k) {
        int lp, rp;
        PARTITION_DUAL(A, p, k, lp, rp);
        QUICK_SORT_DUAL(A, p, lp - 1);
        if (A[lp] < A[rp]) {
            QUICK_SORT_DUAL(A, lp + 1, rp - 1);
        }
        QUICK_SORT_DUAL(A, rp + 1, k);
    }
}

// ==========================================
// 3. BUCKET SORT (Standard)
// ==========================================

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

// ==========================================
// 4. BUCKET SORT (Modified)
// ==========================================

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
        if (index >= n) index = n - 1;
        B[index].push_back(A[i]);
    }

    for (int j = 0; j < n; j++) {
        if (!B[j].empty()) INSERTION_SORT(B[j]);
    }

    int k = 0;
    for (int j = 0; j < n; j++) {
        for (float val : B[j]) A[k++] = val;
    }
}

// ==========================================
// TESTER I MAIN
// ==========================================

template<typename Func, typename DataVector>
void runTest(Func func, string name, DataVector data, int N_size) {

    // Tworzenie kopii danych (bo sortowanie modyfikuje wektor)
    DataVector data_copy = data;

    auto start = high_resolution_clock::now();
    func(data_copy);
    auto end = high_resolution_clock::now();

    duration<double, milli> elapsed = end - start;

    // Wypisujemy w formacie CSV do wykresu: Liczba_Elementów, Nazwa, Czas
    cout << N_size << "," << name << "," << fixed << setprecision(3) << elapsed.count() << endl;
}

int main() {
    // Nagłówek dla pliku CSV/wykresu
    cout << "N, Algorytm, Czas_ms" << endl;

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dist(0.0f, 1.0f);

    // Pętla iterująca przez potęgi dziesiątki: 10, 100, 1000, ... 10,000,000
    for (int p = 1; p <= 7; ++p) {
        const int N = (int)pow(10, p);
        cout << "// --- N = " << N << " --- //" << endl;

        // Generowanie jednego dużego wektora danych dla bieżącego N
        vector<float> data(N);
        for(int i = 0; i < N; i++) {
            data[i] = dist(gen);
        }

        // 1. QUICK SORT (Standard)
        runTest(
            [](vector<float>& arr){ QUICK_SORT(arr, 0, arr.size()-1); },
            "QuickSort",
            data, N
        );

        // 2. QUICK SORT (Dual-Pivot)
        runTest(
            [](vector<float>& arr){ QUICK_SORT_DUAL(arr, 0, arr.size()-1); },
            "QuickSort_Mod",
            data, N
        );

        // 3. BUCKET SORT (Standard)
        runTest(
            [](vector<float>& arr){ BucketSort(arr); },
            "BucketSort",
            data, N
        );

        // 4. BUCKET SORT (Modified - Universal)
        runTest(
            [](vector<float>& arr){ BucketSort_Modfied(arr); },
            "BucketSort_Mod",
            data, N
        );
    }

    return 0;
}