#include <iostream>
#include <vector>
using namespace std;


int LEFT(int i) {
    return 2 * i + 1;
}
int RIGHT(int i) {
    return 2 * i + 2;
}


void HEAPIFY(vector<int>& A, int heap_size, int i) {
    int l = LEFT(i);
    int r = RIGHT(i);
    int largest;

    if (l < heap_size && A[l] > A[i])
        largest = l;
    else
        largest = i;

    if (r < heap_size && A[r] > A[largest])
        largest = r;

    if (i != largest) {
        swap(A[i], A[largest]);
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
    int n = A.size();
    BUILD_HEAP(A);

    int heap_size = n;
    for (int i = n - 1; i >= 1; i--) {
        swap(A[0], A[i]);
        heap_size--;
        HEAPIFY(A, heap_size, 0);
    }
}



// HEAP_SORT z kopce ternarnym.
// Dla każdego i zachodzi:
// A[i] >= A[3*i + 1]
// A[i] >= A[3*i + 2]
// A[i] >= A[3*i + 3]
// W zasadzie zmienia sie tylko algrotym HEAPIFY na HEAPIFY_MODIFIED


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


    if (l < heap_size && A[l] > A[i]) {
        largest = l;
    }
    else {
        largest = i;
    }

    if (m < heap_size && A[m] > A[largest]) {
        largest = m;
    }

    if (r < heap_size && A[r] > A[largest]) {
        largest = r;
    }

    if (i != largest) {
        int temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
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
        heap_size--;
        HEAPIFY_MODIFIED(A, heap_size, 0);
    }
}


int main() {
    vector<int> A = {9, 3, 7, 1, 5, 2, 8, 6, 4, -10};

    HEAP_SORT_MODIFIED(A);
    for (int x : A)
        cout << x << ' ';

    return 0;
}