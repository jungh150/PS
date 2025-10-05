#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<vector<char>> ans(n, vector<char>(n, 'D'));

    int cnt = n * n - k; // 탈출할 수 없는 시작점
    if (cnt == 0) {
    } else if (cnt == 1) {
        cout << "NO\n";
        return;
    } else {
        ans[0][0] = 'R';
        ans[0][1] = 'L';
        cnt -= 2;
        for (int j = 2; j < n; j++) {
            if (cnt <= 0) break;
            ans[0][j] = 'L';
            cnt--;
        }
        for (int i = 1; i < n; i++) {
            if (cnt <= 0) break;
            for (int j = 0; j < n; j++) {
                if (cnt <= 0) break;
                ans[i][j] = 'U';
                cnt--;
            }
        }
    }

    cout << "YES\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << ans[i][j];
        }
        cout << '\n';
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