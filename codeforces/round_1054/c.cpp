#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> cnt(n + 1, 0);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    long long tmp1 = 0;
    for (int i = 0; i < k; i++) { // i는 다 있어야 함
        if (cnt[i] == 0) tmp1++;
    }

    long long tmp2 = cnt[k];

    cout << max(tmp1, tmp2) << '\n';
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