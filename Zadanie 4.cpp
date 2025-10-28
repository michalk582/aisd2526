#include <iostream>
#include <vector>
#include <limits>
using namespace std;
// Plik w zasadzie nie zbyt potrzebny lepiej to wygalda w przyapdku zadania 5

int przypisania = 0;
int porownania = 0;


void INSERTION_SORT(int A[], int n) {
    int x, j;

    for (int i = 1; i < n; i++) {
        x = A[i];
        przypisania++;

        j = i - 1;

        przypisania++;
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

void INSERTION_SORT_MODIFIED(int A[], int n) {
    int i, j, k, x, y, temp;

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
        przypisania++;
        while (k >= 0 && A[k] > y) {
            porownania++;
            A[k + 1] = A[k];
            przypisania++;
            k = k - 1;
        }
        A[k + 1] = y;
        przypisania++;

        j = i - 1;
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



int main() {
    int A[9] = {12, 2, 4, 13, 145, 12, 42, 12, 441};
    vector<int> C = {1, 2, 3, 4};

    // INSERITON_SORT
    przypisania = 0;
    porownania = 0;
    INSERTION_SORT(A, 10);
    cout << "INSERTION_SORT przypisania: " << przypisania << " porównania: " << porownania << endl;


    // INSERITON_SORT_MODIFIED
    przypisania = 0;
    porownania = 0;
    INSERTION_SORT_MODIFIED(A, 10);
    cout << "INSERTION_SORT_MODIFIED przypisania: " << przypisania << " porównania: " << porownania << endl;


    vector<int> B = {12, 2, 4, 13, 145, 12, 42, 12, 441};
    // MERGE_SORT
    przypisania = 0;
    porownania = 0;
    MERGE_SORT(B, 0, B.size() - 1);
    cout << "MERGE_SORT przypisania: " << przypisania << " porównania: " << porownania << endl;


    // MERGE_SORT_MODIFIED
    przypisania = 0;
    porownania = 0;
    MERGE_SORT_MODIFIED(B, 0, B.size() - 1);
    cout << "MERGE_SORT_MODIFIED przypisania: " << przypisania << " porównania: " << porownania << endl;


    // HEAP_SORT
    przypisania = 0;
    porownania = 0;
    HEAP_SORT(B);
    cout << "HEAP_SORT przypisania: " << przypisania << " porównania: " << porownania << endl;


    // HEAP_SORT_MODIFIED
    przypisania = 0;
    porownania = 0;
    HEAP_SORT_MODIFIED(B);
    cout << "HEAP_SORT_MODIFIED przypisania: " << przypisania << " porównania: " << porownania << endl;


}