#include "Zadanie_2.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>


using namespace std;
using namespace std::chrono;


vector<int> przygotuj_ceny(int max_n) {
    vector<int> p;
    srand(42);
    for (int i = 1; i <= max_n; i++) {
        p.push_back((i * 2) + (rand() % 10));
    }
    return p;
}

int main() {
    vector<int> rozmiary = {10, 20, 25, 30, 100, 500, 1000, 2000, 3000};
    vector<int> ceny = przygotuj_ceny(3005);

    ofstream plik("dane.csv");
    plik << "n,naiwna,memo,iter" << endl;

    cout << "testy ";
    cout << left << setw(10) << "N" << setw(18) << "naiwna" << setw(18) << "mem" << setw(18) << "iter" << endl;
    cout << string(65, '-') << endl;

    for (int n : rozmiary) {
        cout << left << setw(10) << n;

        double t_naive = 0.0;
        double t_memo = 0.0;
        double t_iter = 0.0;

        // naiwna
        if (n <= 28) {
            auto start = high_resolution_clock::now();
            CUT_ROD_NAIVE(ceny, n);
            auto stop = high_resolution_clock::now();
            t_naive = duration<double>(stop - start).count();
            cout << left << setw(18) << fixed << setprecision(6) << t_naive;
        } else {
            t_naive = -1.0;
            cout << left << setw(18) << "---";
        }

        // spamietoywanie
        {
            auto start = high_resolution_clock::now();
            MEMOIZED_CUT_ROD(ceny, n);
            auto stop = high_resolution_clock::now();
            t_memo = duration<double>(stop - start).count();
            cout << left << setw(18) << fixed << setprecision(6) << t_memo;
        }

        // iteracja
        {
            auto start = high_resolution_clock::now();
            BOTTOM_UP_CUT_ROD(ceny, n);
            auto stop = high_resolution_clock::now();
            t_iter = duration<double>(stop - start).count();
            cout << left << setw(18) << fixed << setprecision(6) << t_iter;
        }

        plik << n << "," << t_naive << "," << t_memo << "," << t_iter << endl;

        cout << endl;
    }

    plik.close();
    cout << "Dane" << endl;

    return 0;
}