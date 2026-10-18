#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n + 1);
    vector<vector<vector<int>>> cnt(n + 1);

    for (int i = 1; i < n + 1; i++) {
        int x;
        cin >> x;
        a[i] = x;
        int sz = cnt[x].size();
        if (cnt[x].empty()) {
            cnt[x].push_back({i});
        } else if (cnt[x][sz - 1].size() == x) {
            cnt[x].push_back({i});
        } else {
            cnt[x][sz - 1].push_back(i);
        }
    }

    int tcnt = 0;
    for (int i = 1; i < n + 1; i++) {
        int sz = cnt[i].size();
        if (cnt[i].empty()) continue;
        if (cnt[i][sz - 1].size() != i) {
            cout << -1 << '\n';
            return;
        }
        tcnt += (i * sz);
    }

    if (tcnt != n) {
        cout << -1 << '\n';
        return;
    }

    vector<int> b(n + 1);
    int tmp = 1;
    for (int i = 1; i < n + 1; i++) {
        int sz = cnt[i].size();
        if (cnt[i].empty()) continue;
        for (int j = 0; j < sz; j++) {
            for (int idx: cnt[i][j]) {
                b[idx] = tmp;
            }
            tmp++;
        }
    }

    for (int i = 1; i < n + 1; i++) cout << b[i] << ' ';
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