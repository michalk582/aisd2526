#include <iostream>
#include <ostream>
#include <vector>
using namespace std;


int PARTITION(vector<int>& A, int poczatek, int koniec) {
    int pivot = A[koniec];
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

void QUICK_SORT(vector<int>& A, int p, int k) {
    if (p < k) {
        int s = PARTITION(A, p, k); // dzielimy tablicę
        QUICK_SORT(A, p, s - 1); // sortujemy lewa czesc
        QUICK_SORT(A, s + 1, k); // sortujemy prawa czesc
    }
}


int PARTITION_MODIFIED(vector<int>& A, int poczatek, int srodek, int koniec) {
    int pivot = A[koniec];
    int i = poczatek - 1;

}





int main() {
    vector<int> A = {11, 9, 10, 8, 1, 2, 3, 12, 5, 6};
    QUICK_SORT(A, 0, 10);
    for (int i = 0; i < 10; i++) {
        cout << A[i] << " ";
    }
    return 0;
}
