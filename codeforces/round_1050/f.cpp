#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> a(n);
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        a[i] = vector<int>(k);
        for (int j = 0; j < k; j++) cin >> a[i][j];
    }

    sort(a.begin(), a.end());

    for (int x: a[0]) cout << x << ' ';
    int sz = a[0].size();

    while (true) {
        vector<vector<int>> tmp;
        for (int i = 0; i < a.size(); i++) {
            if (a[i].size() > sz) {
                for (int i = 0; i < sz; i++) a[i].erase(a[i].begin());
            }
            tmp.push_back(a[i]);
        }

        if (tmp.empty()) {
            cout << "empty\n";
            break;
        } else {
            cout << "not empty\n";
            break;
        }

        sort(tmp.begin(), tmp.end());

        for (int x: a[0]) cout << x << ' ';
        sz = tmp[0].size();
    }

    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}