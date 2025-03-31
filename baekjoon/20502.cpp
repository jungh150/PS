#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> r(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> r[i];

    vector<vector<pair<int, int>>> ans(m + 1);

    for (int i = 1; i < n + 1; i++) {
        int x; // 키워드 개수
        cin >> x;
        for (int j = 0; j < x; j++) {
            int k; // 키워드
            cin >> k;
            ans[k].emplace_back(r[i], i);
        }
    }

    for (int i = 1; i < m + 1; i++) {
        sort(ans[i].begin(), ans[i].end());
    }

    int q;
    cin >> q;

    while (q--) {
        int x; // 키워드
        cin >> x;

        if (ans[x].empty()) {
            cout << -1 << '\n';
        } else {
            int ansn = ans[x].size();
            for (int i = 0; i < ansn; i++) cout << ans[x][i].second << ' ';
            cout << '\n';
        }
    }
}