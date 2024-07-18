#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m, k, t;
    cin >> n >> m >> k >> t;

    vector<pair<int, int>> e;

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        e.push_back({a, 1});
        e.push_back({b, -1});
    }

    sort(e.begin(), e.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first == b.first) return a.second > b.second;
        return a.first < b.first;
    });

    int curp = 0;
    int maxt = 0;
    int pret = 1;

    for (auto& x : e) {
        int curt = x.first;

        if (curp >= t) {
            maxt += curt - pret;
        }

        curp += x.second;
        pret = curt;
    }

    curp = 0;
    pret = 1;
    int cnt = 0;

    for (auto& x : e) {
        int curt = x.first;

        if (curp >= t) {
            maxt += curt - pret;
        } else if (curp + k >= t) {
            maxt += curt - pret;
            cnt++;
            if (cnt == k) break;
        }

        curp += x.second;
        pret = curt;
    }

    cout << maxt << '\n';
    return 0;
}
