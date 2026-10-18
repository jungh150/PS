#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<vector<int>> b(4, vector<int>(n));
    for (int i = 0; i < n; i++) b[0][i] = a[i];

    for (int i = 1; i < 4; i++) {
        vector<int> cnt(n + 10, 0);
        for (int j = 0; j < n; j++) cnt[b[i - 1][j]]++;

        int mint = n + 10;
        for (int l = 0; l < n + 10; l++) {
            if (cnt[l] == 0) {
                mint = l;
                break;
            }
        }

        for (int j = 0; j < n; j++) {
            cnt[b[i - 1][j]]--; // 자기거 빼기
            if (cnt[b[i - 1][j]] == 0 && b[i - 1][j] < mint) {
                b[i][j] = b[i - 1][j];
            } else {
                b[i][j] = mint;
            }
            cnt[b[i - 1][j]]++; // 자기거 다시 더하기
        }
    }

    long long sumt = 0;
    if (k < 4) {
        for (int x: b[k]) sumt += x;
    } else if (k % 2 == 1) {
        for (int x: b[3]) sumt += x;
    } else {
        for (int x: b[2]) sumt += x;
    }
    cout << sumt << '\n';
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