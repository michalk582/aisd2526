#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct Activity {
    int id;
    int start;
    int finish;
};


bool compareByStart(const Activity& a, const Activity& b) {
    if (a.start != b.start)
        return a.start < b.start;
    return a.finish < b.finish;
}


vector<int> ACTIVITY_SELECTOR_ITERATIVE(vector<Activity> activities) { // kopia wektora
    if (activities.empty()) return {};
    sort(activities.begin(), activities.end(), compareByStart);

    vector<int> result;
    int n = activities.size();

    Activity lastSelected = activities[n - 1];
    result.push_back(lastSelected.id);

    for (int i = n - 2; i >= 0; i--) {
        if (activities[i].finish <= lastSelected.start) {
            result.push_back(activities[i].id);
            lastSelected = activities[i];
        }
    }

    return result;
}


void RECURSIVE_AUX(const vector<Activity>& activities, int k, vector<int>& res) {
    int m = k - 1;
    while (m >= 0 && activities[m].finish > activities[k].start) {
        m--;
    }
    if (m >= 0) {
        res.push_back(activities[m].id);
        RECURSIVE_AUX(activities, m, res);
    }
}

vector<int> ACTIVITY_SELECTOR_RECURSIVE(vector<Activity> activities) {
    if (activities.empty()) return {};
    sort(activities.begin(), activities.end(), compareByStart);

    vector<int> result;
    int n = activities.size();

    result.push_back(activities[n - 1].id);

    RECURSIVE_AUX(activities, n - 1, result);

    return result;
}

// acitvity selector w wersji programowania dynamicznego
vector<int> ACTIVITY_SELECTOR_DP(vector<Activity> activities) {
    if (activities.empty()) return {};
    sort(activities.begin(), activities.end(), compareByStart);
    int n = activities.size();

    vector<int> dp(n, 1);
    vector<int> parent(n, -1);

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (activities[i].start >= activities[j].finish && dp[i] < dp[j] + 1) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
    }

    int maxIndex = 0;
    for (int i = 1; i < n; i++) {
        if (dp[i] > dp[maxIndex]) {
            maxIndex = i;
        }
    }

    // Odzyskanie wyniku
    vector<int> result;
    int curr = maxIndex;
    while (curr != -1) {
        result.push_back(activities[curr].id);
        curr = parent[curr];
    }
    return result;
}

// generowanie danych
vector<Activity> generateData(int n) {
    vector<Activity> data;
    data.reserve(n);
    mt19937 rng(42);
    uniform_int_distribution<int> startDist(0, n);
    uniform_int_distribution<int> durationDist(1, 10);

    for (int i = 0; i < n; i++) {
        int s = startDist(rng);
        int f = s + durationDist(rng);
        data.push_back({i, s, f});
    }
    return data;
}

int main() {
    // test
    cout << "test poprawnosci: " << endl;
    vector<Activity> demoData = {
        {1, 1, 4}, {2, 3, 5}, {3, 0, 6}, {4, 5, 7}, {5, 3, 9},
        {6, 5, 9}, {7, 6, 10}, {8, 8, 11}, {9, 8, 12}, {10, 2, 14}, {11, 12, 16}
    };

    auto resIter = ACTIVITY_SELECTOR_ITERATIVE(demoData);
    auto resRec  = ACTIVITY_SELECTOR_RECURSIVE(demoData);
    auto resDP   = ACTIVITY_SELECTOR_DP(demoData);

    cout << "Wynik Iteracyjny (rozmiar " << resIter.size() << "): ";
    for(int id : resIter) cout << id << " "; cout << endl;

    cout << "Wynik Rekurencyjny (rozmiar " << resRec.size() << "): ";
    for(int id : resRec) cout << id << " "; cout << endl;

    cout << "Wynik DP (rozmiar " << resDP.size() << "): ";
    for(int id : resDP) cout << id << " "; cout << endl;

    // testy wydajnosci i druk danych
    vector<int> sizes = {10, 100, 500, 1000, 2000, 3000};

    ofstream file("dane_act_dp.csv");
    file << "n,iter,rec,dp" << endl;

    cout << left << setw(10) << "N"
         << setw(15) << "Iter [s]"
         << setw(15) << "Rec [s]"
         << setw(15) << "DP [s]" << endl;
    cout << string(55, '-') << endl;

    for (int n : sizes) {
        cout << left << setw(10) << n;
        vector<Activity> data = generateData(n);

        // Iteracyjny
        auto start = high_resolution_clock::now();
        ACTIVITY_SELECTOR_ITERATIVE(data);
        auto stop = high_resolution_clock::now();
        double t_iter = duration<double>(stop - start).count();
        cout << left << setw(15) << fixed << setprecision(6) << t_iter;

        // Rekurencyjny
        start = high_resolution_clock::now();
        ACTIVITY_SELECTOR_RECURSIVE(data);
        stop = high_resolution_clock::now();
        double t_rec = duration<double>(stop - start).count();
        cout << left << setw(15) << fixed << setprecision(6) << t_rec;

        // DP
        start = high_resolution_clock::now();
        ACTIVITY_SELECTOR_DP(data);
        stop = high_resolution_clock::now();
        double t_dp = duration<double>(stop - start).count();
        cout << left << setw(15) << fixed << setprecision(6) << t_dp;

        file << n << "," << t_iter << "," << t_rec << "," << t_dp << endl;
        cout << endl;
    }

    file.close();
    cout << endl;
    cout << "Testy zakonczone." << endl;

    return 0;
}