#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<bool> used(n + 1, false);
    vector<int> idx(n + 1, -1); // 가장 마지막 인덱스

    vector<int> a(n);
    // vector<int> ans;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        idx[a[i]] = i;
        if (!used[a[i]]) {
            used[a[i]] = true;
            // ans.push_back(a[i]);
        }
    }

    vector<pair<int, int>> tmp;
    for (int x = 1; x < n + 1; x++) {
        if (used[x]) {
            tmp.emplace_back(idx[x], x);
        }
    }

    sort(tmp.begin(), tmp.end());

    for (int x = 1; x < n + 1; x++) {
        if (!used[x]) {
            cout << x << ' ';
            // ans.push_back(x);
            k--;
            if (k == 0) {
                cout << '\n';
                return;
            }
        }
    }

    // for (int x: ans) {
    //     cout << x << ' ';
    //     k--;
    //     if (k == 0) {
    //         cout << '\n';
    //         return;
    //     }
    // }

    for (auto [idxt, xt]: tmp) {
        cout << xt << ' ';
        k--;
        if (k == 0) {
            cout << '\n';
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}