#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t, m, n;
    cin >> t >> m >> n;

    vector<pair<int, string>> tr;

    for (int i = 0; i < t; i++) {
        string tn;
        cin >> tn;
        while (true) {
            int tmp;
            cin >> tmp;
            if (tmp == -1) break;
            else tr.emplace_back(tmp, tn);
        }
    }

    sort(tr.begin(), tr.end());

    int trs = tr.size();

    int tmpi = 0;
    for (int i = 0; i < trs; i++) {
        if (m < tr[i].first) {
            tmpi = i;
            break;
        }
    }

    int idx = (n - 1 + tmpi) % trs;

    cout << tr[idx].second << '\n';
}