#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>

using namespace std;
using namespace std::chrono;


int CUT_ROD_NAIVE(const vector<int>& p, int n) {
    if (n == 0) return 0;
    int q = INT_MIN;
    for (int i = 1; i <= n; i++) {
        q = max(q, p[i - 1] + CUT_ROD_NAIVE(p, n - i));
    }
    return q;
}

// rekurencja ze spamietywaniem + odzyskanie rozwiazan
int MEMOIZED_AUX(const vector<int>& p, int n, vector<int>& r, vector<int>& s) {
    if (r[n] >= 0) return r[n];
    
    int q;
    if (n == 0) {
        q = 0;
    } else {
        q = INT_MIN;
        for (int i = 1; i <= n; i++) {
            int current_val = p[i - 1] + MEMOIZED_AUX(p, n - i, r, s);
            if (q < current_val) {
                q = current_val;
                s[n] = i;
            }
        }
    }
    r[n] = q;
    return q;
}


pair<int, vector<int>> CUT_ROD_MEMOIZED(const vector<int>& p, int n) {
    vector<int> r(n + 1, INT_MIN);
    vector<int> s(n + 1, 0);
    
    int max_profit = MEMOIZED_AUX(p, n, r, s);

    vector<int> cuts;
    int temp_n = n;
    while (temp_n > 0) {
        cuts.push_back(s[temp_n]);
        temp_n = temp_n - s[temp_n];
    }
    return {max_profit, cuts};
}

// iteracja + odzyskiwanie
pair<int, vector<int>> CUT_ROD_BOTTOM_UP(const vector<int>& p, int n) {
    vector<int> r(n + 1);
    vector<int> s(n + 1);
    r[0] = 0;

    for (int j = 1; j <= n; j++) {
        int q = INT_MIN;
        for (int i = 1; i <= j; i++) {
            if (q < p[i - 1] + r[j - i]) {
                q = p[i - 1] + r[j - i];
                s[j] = i;
            }
        }
        r[j] = q;
    }

    // Odzyskiwanie rozwiązania
    vector<int> cuts;
    int temp_n = n;
    while (temp_n > 0) {
        cuts.push_back(s[temp_n]);
        temp_n = temp_n - s[temp_n];
    }
    return {r[n], cuts};
}

//
vector<int> generatePrices(int n) {
    vector<int> p;
    mt19937 rng(42);
    uniform_int_distribution<int> dist(0, 5);
    
    int current_price = 0;
    for (int i = 1; i <= n; i++) {
        current_price += (rng() % 3 == 0) ? 2 : 3;
        p.push_back(current_price); 
    }
    return p;
}

int main() {
    cout << "testy : " << endl;
    vector<int> prices = {1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int n_demo = 7;
    
    cout << "Dlugosc preta: " << n_demo << endl;

    cout << "Naive Profit: " << CUT_ROD_NAIVE(prices, n_demo) << endl;

    // spamietywanie
    auto resMemo = CUT_ROD_MEMOIZED(prices, n_demo);
    cout << "Memo Profit:  " << resMemo.first << " | Cuts: ";
    for (int c : resMemo.second) cout << c << " ";
    cout << endl;

    // iteracja
    auto resIter = CUT_ROD_BOTTOM_UP(prices, n_demo);
    cout << "Iter Profit:  " << resIter.first << " | Cuts: ";
    for (int c : resIter.second) cout << c << " ";
    cout << endl;
    cout << string(40, '-') << endl << endl;

    // testy wydajnosci
    vector<int> sizes = {10, 20, 25, 30, 100, 500, 1000, 2000, 3000};
    
    ofstream file("dane_cut_rod.csv");
    file << "n,naive,memo,iter" << endl;

    cout << left << setw(10) << "N" 
         << setw(15) << "Naive [s]" 
         << setw(15) << "Memo [s]" 
         << setw(15) << "Iter [s]" << endl;
    cout << string(55, '-') << endl;

    for (int n : sizes) {
        cout << left << setw(10) << n;

        vector<int> p = generatePrices(n);

        double t_naive = -1.0;
        if (n <= 25) {
            auto start = high_resolution_clock::now();
            CUT_ROD_NAIVE(p, n);
            auto stop = high_resolution_clock::now();
            t_naive = duration<double>(stop - start).count();
            cout << left << setw(15) << fixed << setprecision(6) << t_naive;
        } else {
            cout << left << setw(15) << "---";
        }

        // Mem (O(n^2))
        double t_memo = 0.0;
        {
            auto start = high_resolution_clock::now();
            CUT_ROD_MEMOIZED(p, n);
            auto stop = high_resolution_clock::now();
            t_memo = duration<double>(stop - start).count();
            cout << left << setw(15) << fixed << setprecision(6) << t_memo;
        }

        // Iter (O(n^2))
        double t_iter = 0.0;
        {
            auto start = high_resolution_clock::now();
            CUT_ROD_BOTTOM_UP(p, n);
            auto stop = high_resolution_clock::now();
            t_iter = duration<double>(stop - start).count();
            cout << left << setw(15) << fixed << setprecision(6) << t_iter;
        }

        file << n << "," << t_naive << "," << t_memo << "," << t_iter << endl;
        cout << endl;
    }

    file.close();
    cout << endl;
    cout << "Testy zakonczone." << endl;

    return 0;
}