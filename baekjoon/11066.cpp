#include <iostream>
#include <queue>
using namespace std;

int n;
vector<int> suma;
vector<vector<int>> dp;

int td(int l, int r) {
    if (dp[l][r] != -1) return dp[l][r];
    if (l == r) return 0;
    int cost = 1e9;
    for (int m = l; m < r; m++) {
        cost = min(cost, td(l, m) + td(m + 1, r));
    }
    return dp[l][r] = cost + suma[r] - suma[l - 1];
}

void solve() {
    cin >> n;

    suma = vector<int>(n + 1, 0);
    dp = vector<vector<int>>(n + 1, vector<int>(n + 1, -1));

    for (int i = 1; i < n + 1; i++) {
        int x;
        cin >> x;
        suma[i] = suma[i - 1] + x;
    }

    cout << td(1, n) << '\n';
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