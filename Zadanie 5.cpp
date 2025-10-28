//
// Created by Michał Kasjaniuk on 27/10/2025.
//

// Zadanie 5 w zasadzie 4 tez


#include <iostream>
#include <vector>
#include <limits>
#include <algorithm> // do generate, copy
#include <chrono>    // do pomiaru czasu
#include <cstdlib>   // do rand()
#include <numeric>

using namespace std;
using namespace chrono;


long long porownania = 0;
long long przypisania = 0;



/// Na potrzebę testów algorytm został zmodyfikowany, chodzi o zmienna wejściową
void INSERTION_SORT(vector<int>& A) {
    int x, j, n = A.size();

    for (int i = 1; i < n; i++) {
        x = A[i];
        przypisania++;

        j = i - 1;

        porownania ++;
        while (j >= 0 && A[j] > x) {
            porownania++;
            A[j + 1] = A[j];
            przypisania++;

            j = j - 1;
        }
        A[j + 1] = x;
        przypisania++;
    }
}

void INSERTION_SORT_MODIFIED(vector<int>& A) {
    int i, j, k, x, y, temp, n = A.size();

    for (i = 1; i < n; i += 2) {
        x = A[i];
        przypisania++;
        y = A[i - 1];
        przypisania++;

        porownania++;
        if (y > x) {
            temp = x;
            przypisania++;
            x = y;
            przypisania++;
            y = temp;
            przypisania++;
        }

        k = i - 2;
        porownania++;
        while (k >= 0 && A[k] > y) {
            porownania++;
            A[k + 1] = A[k];
            przypisania++;
            k = k - 1;
        }
        A[k + 1] = y;
        przypisania++;

        j = i - 1;
        porownania++;
        while (j >= 1 && A[j] > x) {
            porownania++;
            A[j + 1] = A[j];
            przypisania++;
            j = j - 1;
        }
        A[j + 1] = x;
        przypisania++;
    }

    porownania++;
    if (n % 2 == 1) {
        i = n - 1;
        x = A[i];
        przypisania++;
        j = i - 1;
        porownania++;
        while (j >= 0 && A[j] > x) {
            porownania++;
            A[j + 1] = A[j];
            przypisania++;
            j = j - 1;
        }
        A[j + 1] = x;
        przypisania++;
    }
}



void MERGE(vector<int>& A, int p, int s, int k) {
    int n1 = s - p + 1;
    int n2 = k - s;

    // tworzymy wektory pomocnicze L i R z wartownikami
    vector<int> L(n1 + 1);
    vector<int> R(n2 + 1);

    // kopiujemy elementy do L i R
    for (int i = 0; i < n1; i++) {
        L[i] = A[p + i];
        przypisania++;
    }
    for (int j = 0; j < n2; j++) {
        R[j] = A[s + 1 + j];
        przypisania++;
    }

    // wartownicy (strażnicy)
    L[n1] = numeric_limits<int>::max();
    R[n2] = numeric_limits<int>::max();

    int i = 0, j = 0;

    // scalanie elementów z L i R do A
    for (int l = p; l <= k; l++) {
        porownania++;
        if (L[i] <= R[j]) {
            A[l] = L[i];
            przypisania++;
            i++;
        } else {
            A[l] = R[j];
            przypisania++;
            j++;
        }
    }
}

void MERGE_SORT(vector<int>& A, int p, int k) {
    porownania++;
    if (p < k) {
        int s = floor((p + k) / 2); // punkt podziału

        MERGE_SORT(A, p, s);
        MERGE_SORT(A, s + 1, k);
        MERGE(A, p, s, k);
    }
}


void MERGE_MODIFIED(vector<int>& A, int p, int s1, int s2, int k) {
    int n1 = s1 - p + 1;
    int n2 = s2 - s1;
    int n3 = k - s2;

    vector<int> L(n1 + 1);
    vector<int> M(n2 + 1);
    vector<int> R(n3 + 1);

    // skopiowanie do tablic
    for (int i = 0; i < n1; i++) {
        L[i] = A[p + i];
        przypisania++;
    }
    for (int j = 0; j < n2; j++) {
        M[j] = A[s1 + 1 + j];
        przypisania++;
    }
    for (int l = 0; l < n3; l++) {
        R[l] = A[s2 + 1 + l];
        przypisania++;
    }

    // wartownicy (strażnicy) dla trzech podtablic
    L[n1] = numeric_limits<int>::max();
    M[n2] = numeric_limits<int>::max();
    R[n3] = numeric_limits<int>::max();

    int i = 0, j = 0, l = 0;

    // Scalanie trzech tablic
    for (int m = p; m <= k; m++) {
        porownania++;
        porownania++;
        if (L[i] <= M[j] && L[i] <= R[l]) {
            A[m] = L[i];
            przypisania++;
            i++;
        }
        else {
            porownania++;
            porownania++;
            // Gdzie kazdy warunek to porowananie, bo porownujemy konkretne dane tablicy
            if (M[j] <= L[i] && M[j] <= R[l]) {
                A[m] = M[j];
                przypisania++;
                j++;
            }
            else {
                A[m] = R[l];
                przypisania++;
                l++;
            }
        }
    }
}

void MERGE_SORT_MODIFIED(vector<int>& A, int p, int k) {
    porownania++;
    if (p < k) {
        int s1 = p + (k - p) / 3, s2 = p + 2 * (k - p) / 3;
        MERGE_SORT_MODIFIED(A, p, s1);
        MERGE_SORT_MODIFIED(A, s1 + 1, s2);
        MERGE_SORT_MODIFIED(A, s2 + 1, k);
        MERGE_MODIFIED(A, p, s1, s2, k);
    }
}



int LEFT(int i) {
    return 2 * i + 1;
}
int RIGHT(int i) {
    return 2 * i + 2;
}

void HEAPIFY(vector<int>& A, int heap_size, int i) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int largest, temp;

    porownania++;
    if (l < heap_size && A[l] > A[i]) {
        largest = l;
    }

    else {
        largest = i;
    }

    porownania++;
    if (r < heap_size && A[r] > A[largest]) {
        largest = r;
    }

    if (i != largest) {
        temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        przypisania++;
        przypisania++;
        HEAPIFY(A, heap_size, largest);
    }
}

void BUILD_HEAP(vector<int>& A) {
    int n = A.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        HEAPIFY(A, n, i);
    }
}

void HEAP_SORT(vector<int>& A) {
    int n = A.size(), temp;
    BUILD_HEAP(A);

    int heap_size = n;
    for (int i = n - 1; i >= 1; i--) {
        temp = A[i];
        A[i] = A[0];
        A[0] = temp;
        przypisania++;
        przypisania++;
        heap_size--;
        HEAPIFY(A, heap_size, 0);
    }
}

int LEFT_MODIFIED(int i) {
    return 3 * i + 1;
}

int MIDDLE_MODIFIED(int i) {
    return 3 * i + 2;
}

int RIGHT_MODIFIED(int i) {
    return 3 * i + 3;
}


void HEAPIFY_MODIFIED(vector<int>& A, int heap_size, int i) {
    int l = LEFT_MODIFIED(i);
    int m = MIDDLE_MODIFIED(i);
    int r = RIGHT_MODIFIED(i);
    int largest;


    porownania++;
    if (l < heap_size && A[l] > A[i]) {
        largest = l;
    }
    else {
        largest = i;
    }

    porownania++;
    if (m < heap_size && A[m] > A[largest]) {
        largest = m;
    }

    porownania++;
    if (r < heap_size && A[r] > A[largest]) {
        largest = r;
    }

    if (i != largest) {
        int temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        przypisania++;
        przypisania++;
        HEAPIFY_MODIFIED(A, heap_size, largest);
    }
}

void BUILD_HEAP_MODIFIED(vector<int>& A) {
    int n = A.size();
    for (int i = n / 2 - 1; i >= 0; i--) {
        HEAPIFY_MODIFIED(A, n, i);
    }
}

void HEAP_SORT_MODIFIED(vector<int>& A) {
    int n = A.size();

    BUILD_HEAP_MODIFIED(A);
    int heap_size = n;
    for (int i = n - 1; i >= 1; i--) {
        int temp = A[i];
        A[i] = A[0];
        A[0] = temp;
        przypisania++;
        przypisania++;
        heap_size--;
        HEAPIFY_MODIFIED(A, heap_size, 0);
    }
}

// Owijka (wrapper) dla MERGE_SORT
void MERGE_SORT_WRAPPER(vector<int>& A) {
    MERGE_SORT(A, 0, A.size() - 1);
}

// Jeśli masz też MERGE_SORT_MODIFIED:
void MERGE_SORT_MODIFIED_WRAPPER(vector<int>& A) {
    MERGE_SORT_MODIFIED(A, 0, A.size() - 1);
}
// HEAP SORT
void HEAP_SORT_WRAPPER(vector<int>& A) {
    HEAP_SORT(A);
}

// HEAP SORT MODIFIED
void HEAP_SORT_MODIFIED_WRAPPER(vector<int>& A) {
    HEAP_SORT_MODIFIED(A);
}


void resetCounters() {
    porownania = 0;
    przypisania = 0;
}

// pomocnicza funkcja do drukowania wyników
void printResults(string name, double czas_ms) {
    cout << name << ":\n";
    cout << "  porównania: " << porownania << endl;
    cout << "  przypisania: " << przypisania << endl;
    cout << "  czas: " << czas_ms << " ms\n\n";
}


// funkcja testująca jeden algorytm
template<typename SortFunc>
void testAlgorithm(SortFunc sortFunc, string name, vector<int> data) {
    resetCounters();

    auto start = high_resolution_clock::now();
    sortFunc(data);
    auto end = high_resolution_clock::now();

    double duration = duration_cast<microseconds>(end - start).count() / 1000.0;
    printResults(name, duration);
}




int main() {
    // generujemy dane testowe
    int n = 1000;  // rozmiar tablicy
    vector<int> data(n);
    generate(data.begin(), data.end(), rand);

    // kopie, żeby każdy algorytm miał te same dane
    vector<int> data1 = data;
    vector<int> data2 = data;
    vector<int> data3 = data;
    vector<int> data4 = data;
    vector<int> data5 = data;
    vector<int> data6 = data;



    // testujemy każdy algorytm dla losowego przypadku
    cout << "1. Test dla losowej tablicy:  " << endl;
    testAlgorithm(INSERTION_SORT, "INSERTION_SORT", data1);
    testAlgorithm(INSERTION_SORT_MODIFIED, "INSERTION_SORT_MODIFIED", data2);
    testAlgorithm(MERGE_SORT_WRAPPER, "MERGE_SORT", data3);
    testAlgorithm(MERGE_SORT_MODIFIED_WRAPPER, "MERGE_SORT_MODIFIED", data4);
    testAlgorithm(HEAP_SORT_WRAPPER, "HEAP_SORT", data5);
    testAlgorithm(HEAP_SORT_MODIFIED_WRAPPER, "HEAP_SORT_MODIFIED", data6);
    cout << endl;


    // Generowanie danych do wersji optymistycznej i pesymis
    vector<int> B(1000);
    iota(B.begin(), B.end(), 0);
    vector<int> B1 = B;
    vector<int> B2 = B;
    vector<int> B3 = B;
    vector<int> B4 = B;
    vector<int> B5 = B;
    vector<int> B6 = B;

    // Tablice w wersji najbardziej optymistycznej:
    cout << "2. Test dla najbardziej optymistycznej tablicy:  " << endl;
    testAlgorithm(INSERTION_SORT, "INSERTION_SORT", B1);
    testAlgorithm(INSERTION_SORT_MODIFIED, "INSERTION_SORT_MODIFIED", B2);
    testAlgorithm(MERGE_SORT_WRAPPER, "MERGE_SORT", B3);
    testAlgorithm(MERGE_SORT_MODIFIED_WRAPPER, "MERGE_SORT_MODIFIED", B4);
    testAlgorithm(HEAP_SORT_WRAPPER, "HEAP_SORT", B5);
    testAlgorithm(HEAP_SORT_MODIFIED_WRAPPER, "HEAP_SORT_MODIFIED", B6);


    // Generowanie dla bardziej pesymistycznych
    vector<int> C(1000);
    iota(C.begin(), C.end(),0);
    reverse(C.begin(), C.end());
    vector<int> C1 = C;
    vector<int> C2 = C;
    vector<int> C3 = C;
    vector<int> C4 = C;
    vector<int> C5 = C;
    vector<int> C6 = C;


    // Tablica w wersji najbardziej pesymistycznej:
    cout << "3. Test dla najbardziej pesymistycznej tablicy:  " << endl;
    testAlgorithm(INSERTION_SORT, "INSERTION_SORT", C1);
    testAlgorithm(INSERTION_SORT_MODIFIED, "INSERTION_SORT_MODIFIED", C2);
    testAlgorithm(MERGE_SORT_WRAPPER, "MERGE_SORT", C3);
    testAlgorithm(MERGE_SORT_MODIFIED_WRAPPER, "MERGE_SORT_MODIFIED", B4);
    testAlgorithm(HEAP_SORT_WRAPPER, "HEAP_SORT", C5);
    testAlgorithm(HEAP_SORT_MODIFIED_WRAPPER, "HEAP_SORT_MODIFIED", C6);



    // Tablica losowa dla duzych danych:
    int m = 100000;  // rozmiar tablicy
    vector<int> D(m);
    generate(D.begin(), D.end(), rand);

    // kopie, żeby każdy algorytm miał te same dane
    vector<int> D1 = D;
    vector<int> D2 = D;
    vector<int> D3 = D;
    vector<int> D4 = D;
    vector<int> D5 = D;
    vector<int> D6 = D;

    // testujemy każdy algorytm dla losowego przypadku
    cout << "4. Dane dla dużej talicy (n = 100000) " << endl;
    testAlgorithm(INSERTION_SORT, "INSERTION_SORT", D1);
    testAlgorithm(INSERTION_SORT_MODIFIED, "INSERTION_SORT_MODIFIED", D2);
    testAlgorithm(MERGE_SORT_WRAPPER, "MERGE_SORT", D3);
    testAlgorithm(MERGE_SORT_MODIFIED_WRAPPER, "MERGE_SORT_MODIFIED", D4);
    testAlgorithm(HEAP_SORT_WRAPPER, "HEAP_SORT", D5);
    testAlgorithm(HEAP_SORT_MODIFIED_WRAPPER, "HEAP_SORT_MODIFIED", D6);

    return 0;

}
