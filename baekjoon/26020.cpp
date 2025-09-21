#include <iostream>
#include <vector>
using namespace std;

string s;
vector<int> a;
int n;
vector<bool> chk;
int ans = 1e6;

void dpf(vector<int> pm) {
    vector<vector<int>> dp(n, vector<int>(4));
    dp[0][a[0]] = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            if (a[i] == pm[j]) dp[i][j] = min(dp[i - 1][pm[j]], dp[i - 1][pm[j - 1]]);
            else dp[i][pm[j]] = dp[i - 1][pm[j]] + 1;
        }
    }
    ans = min(ans, dp[n - 1][3]);
}

void bt(int cnt, vector<int> res) {
    if (cnt >= 4) {
        dpf(res);
        return;
    }
    for (int i = 0; i < 4; i++) {
        if (!chk[i]) {
            chk[i] = true;
            res.push_back(i);
            bt(cnt + 1, res);
            chk[i] = false;
            res.pop_back();
        }
    }
}

void solve() {
    cin >> s;
    n = s.size();

    a = vector<int>(n);
    for (int i = 0; i < n; i++) {
        if (s[i] == 'h') a[i] = 0;
        else if (s[i] == 'd') a[i] = 1;
        else if (s[i] == 'c') a[i] = 2;
        else if (s[i] == 's') a[i] = 3;
    }

    chk = vector<bool>(4, 0);
    bt(0, {});

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}