#include <iostream>
#include <vector>
using namespace std;

vector<int> a;
vector<vector<int>> dp;

int td(int l, int r) {
    if (dp[l][r] != -1) return dp[l][r];
    if (l == r) return a[l];
    return dp[l][r] = max(a[l] - td(l + 1, r), a[r] - td(l, r - 1));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        a = vector<int>(n);
        int sumt = 0; // 전체 점수 = 내 점수 + 상대 점수
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            sumt += a[i];
        }

        dp = vector<vector<int>>(n, vector<int>(n, -1));
        // dp[i][j]: 구간 [l, r]에서 (내 점수 - 상대 점수)의 최댓값

        // 내 점수 = (전체 점수 + dp[][]) / 2
        cout << (sumt + td(0, n - 1)) / 2 << '\n';
    }
}