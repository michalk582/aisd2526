#include <iostream>
using namespace std;

// Zadanie 1
void INSERTION_SORT(int A[], int n) {
    int x, j;

    for (int i = 1; i < n; i++) {
        x = A[i];
        j = i - 1;
        while (j >= 0 && A[j] > x) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = x;
    }
}

void INSERTION_SORT_MODIFIED(int A[], int n) {
    int i, j, k, x, y, temp;

    for (i = 1; i < n; i += 2) {
        x = A[i];
        y = A[i - 1];

        if (y > x) {
            temp = x;
            x = y;
            y = temp;
        }

        k = i - 2;
        while (k >= 0 && A[k] > y) {
            A[k + 1] = A[k];
            k = k - 1;
        }
        A[k + 1] = y;

        j = i - 1;
        while (j >= 1 && A[j] > x) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = x;
    }

    if (n % 2 == 1) {
        i = n - 1;
        x = A[i];
        j = i - 1;
        while (j >= 0 && A[j] > x) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = x;
    }
}


int main() {
    int A[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    INSERTION_SORT(A, 10);
    for (int i = 0; i < 10; i++) {
        cout << A[i] << " ";
    }

}
