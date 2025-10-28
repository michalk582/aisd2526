#include <iostream>
#include <vector>
#include <limits>

using namespace std;

// Funkcja scala dwie posortowane części wektora A[p..s] i A[s+1..k]
void MERGE(vector<int>& A, int p, int s, int k) {
    int n1 = s - p + 1;
    int n2 = k - s;

    // tworzymy wektory pomocnicze L i R z wartownikami
    vector<int> L(n1 + 1);
    vector<int> R(n2 + 1);

    // kopiujemy elementy do L i R
    for (int i = 0; i < n1; i++)
        L[i] = A[p + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[s + 1 + j];

    // wartownicy (strażnicy)
    L[n1] = numeric_limits<int>::max();
    R[n2] = numeric_limits<int>::max();

    int i = 0, j = 0;

    // scalanie elementów z L i R do A
    for (int l = p; l <= k; l++) {
        if (L[i] <= R[j]) {
            A[l] = L[i];
            i++;
        } else {
            A[l] = R[j];
            j++;
        }
    }
}

// Rekurencyjny Merge Sort
void MERGE_SORT(vector<int>& A, int p, int k) {
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
    }
    for (int j = 0; j < n2; j++) {
        M[j] = A[s1 + 1 + j];
    }
    for (int l = 0; l < n3; l++) {
        R[l] = A[s2 + 1 + l];
    }

    // wartownicy (strażnicy) dla trzech podtablic
    L[n1] = numeric_limits<int>::max();
    M[n2] = numeric_limits<int>::max();
    R[n3] = numeric_limits<int>::max();

    int i = 0, j = 0, l = 0;

    // Scalanie trzech tablic
    for (int m = p; m <= k; m++) {
        if (L[i] <= M[j] && L[i] <= R[l]) {
            A[m] = L[i];
            i++;
        }
        else {
            if (M[j] <= L[i] && M[j] <= R[l]) {
                A[m] = M[j];
                j++;
            }
            else {
                A[m] = R[l];
                l++;
            }
        }
    }
}

void MERGE_SORT_MODIFIED(vector<int>& A, int p, int k) {
    if (p < k) {
        int s1 = p + (k - p) / 3, s2 = p + 2 * (k - p) / 3;
        MERGE_SORT_MODIFIED(A, p, s1);
        MERGE_SORT_MODIFIED(A, s1 + 1, s2);
        MERGE_SORT_MODIFIED(A, s2 + 1, k);
        MERGE_MODIFIED(A, p, s1, s2, k);
    }
}



int main() {
    vector<int> A = {10, 1, 23, 12, 32, 12, 421, 4124};
    // MERGE_SORT(A, 0, A.size() - 1); // sortujemy całą tablicę
    MERGE_SORT_MODIFIED(A, 0, A.size() - 1);

    for (int i = 0; i < A.size(); i++) {
        cout << A[i] << " ";
    }

    return 0;
}