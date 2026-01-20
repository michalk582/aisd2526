#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>    // Do mierzenia czasu
#include <random>    // Do generowania losowych liter
#include <fstream>   // Do zapisu do pliku
#include <iomanip>   // Do ładnej tabelki

using namespace std;
using namespace std::chrono;


vector<vector<int>> LCS_ITERATIVE(const string& X, const string& Y) {
    int m = X.length();
    int n = Y.length();

    vector<vector<int>> c(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
            } else {
                c[i][j] = max(c[i - 1][j], c[i][j - 1]);
            }
        }
    }
    return c;
}


int LCS_MEMO_AUX(const string& X, const string& Y, int i, int j, vector<vector<int>>& c) {
    if (i == 0 || j == 0) return 0;
    if (c[i][j] != -1) return c[i][j];

    if (X[i - 1] == Y[j - 1]) {
        c[i][j] = 1 + LCS_MEMO_AUX(X, Y, i - 1, j - 1, c);
    } else {
        c[i][j] = max(LCS_MEMO_AUX(X, Y, i, j - 1, c),
                      LCS_MEMO_AUX(X, Y, i - 1, j, c));
    }
    return c[i][j];
}

vector<vector<int>> LCS_RECURSIVE(const string& X, const string& Y) {
    int m = X.length();
    int n = Y.length();
    vector<vector<int>> c(m + 1, vector<int>(n + 1, -1));
    LCS_MEMO_AUX(X, Y, m, n, c);
    return c;
}


string GET_LCS_STRING(const vector<vector<int>>& c, const string& X, const string& Y) {
    string lcs = "";
    int i = X.length();
    int j = Y.length();

    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs += X[i - 1];
            i--; j--;
        } else if (c[i - 1][j] >= c[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    reverse(lcs.begin(), lcs.end());
    return lcs;
}


string generator_danych(int length) {
    const string characters = "ACGT";
    string randomString;
    randomString.reserve(length);

    static mt19937 rng(42);
    static uniform_int_distribution<> dist(0, characters.size() - 1);

    for (int i = 0; i < length; ++i) {
        randomString += characters[dist(rng)];
    }
    return randomString;
}

// testy
int main() {
    // weryfikacja porpawnosci i odzyskanie wynikow
    string X_demo = "ABCBDAB";
    string Y_demo = "BDCABA";
    auto tab = LCS_ITERATIVE(X_demo, Y_demo);
    string res = GET_LCS_STRING(tab, X_demo, Y_demo);
    cout << "test poprawosci " << X_demo << " i " << Y_demo << " -> LCS: " << res << endl;

    vector<int> sizes = {10, 50, 100, 500, 1000, 2000, 3000, 4000, 5000};

    ofstream file("dane_lcs.csv");
    file << "n,iter,rec" << endl;

    cout << "testy;" << endl;
    cout << left << setw(10) << "n" << setw(15) << "iter [s]" << setw(15) << "rec [s]" << endl;
    cout << string(40, '-') << endl;

    for (int n : sizes) {
        cout << left << setw(10) << n;

        string S1 = generator_danych(n);
        string S2 = generator_danych(n);

        double t_iter = 0;
        {
            auto start = high_resolution_clock::now();
            LCS_ITERATIVE(S1, S2);
            auto stop = high_resolution_clock::now();
            t_iter = duration<double>(stop - start).count();
        }
        cout << left << setw(15) << fixed << setprecision(6) << t_iter;


        double t_rec = 0;
        // argument potrzebny, aby nasza wersja naiwna sie nie wywaliła
        if (n <= 5000) {
            auto start = high_resolution_clock::now();
            LCS_RECURSIVE(S1, S2);
            auto stop = high_resolution_clock::now();
            t_rec = duration<double>(stop - start).count();
            cout << left << setw(15) << fixed << setprecision(6) << t_rec;
        } else {
            t_rec = -1.0;
            cout << left << setw(15) << "--- (skip)";
        }

        file << n << "," << t_iter << "," << t_rec << endl;
        cout << endl;
    }

    file.close();
    cout << "test wykonany" << endl;

    return 0;
}