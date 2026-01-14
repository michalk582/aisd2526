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
        int s = PARTITION(A, p, k);
        QUICK_SORT(A, p, s - 1);
        QUICK_SORT(A, s + 1, k);
    }
}



void PARTITION_DUAL(vector<int>& A, int p, int k, int& lp, int& rp) {
    if (A[p] > A[k]) {
        swap(A[p], A[k]);
    }

    int pivot1 = A[p];
    int pivot2 = A[k];

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

void QUICK_SORT_DUAL(vector<int>& A, int p, int k) {
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




int main() {
    vector<int> A = {11, 9, 10, 8, 1, 2, 3, 12, 5, 6};
    vector<int> B = {1, 2, 123, 4, 5, 6, 7, 8, 9, 10};
    QUICK_SORT(B, 0, 9);
    QUICK_SORT_DUAL(A, 0, 9);
    for (int i = 0; i < 10; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 10; i++) {
        cout << B[i] << " ";
    }
    return 0;
}
