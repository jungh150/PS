#include <bits/stdc++.h>
using namespace std;

void solve() {
    int w, h;
    cin >> w >> h;

    vector<pair<int, int>> ans;

    for (int i = h; i > 1; i--) {
        for (int j = 1; j < w; j++) {
            ans.emplace_back(i, j);
        }
    }

    for (int j = 1; j < w; j++) {
        if ((1 + j) % 2 == 1) ans.emplace_back(1, j);
    }

    for (int i = 1; i < h; i++) {
        if ((i + w) % 2 == 1) ans.emplace_back(i, w);
    }

    int sz = ans.size();
    cout << sz << '\n';
    for (int i = 0; i < sz; i++) {
        cout << ans[i].second << ' ' << ans[i].first << '\n';
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