#include <bits/stdc++.h>
using namespace std;

vector<int> pcnt;

void solve() {
    int n, k;
    cin >> n >> k;

    int sumt = n * (n - 1) / 2;
    int ans = sumt - k; // 오름차순 쌍 개수

    if (ans == 0) {
        for (int i = n; i > 0; i--) cout << i << ' ';
        cout << '\n';
        return;
    }

    if (ans == sumt) {
        for (int i = 1; i < n + 1; i++) cout << i << ' ';
        cout << '\n';
        return;
    }

    // dp[i][j]: i번째 수까지 확인했을 때, 정확히 j개를 만들 수 있는지 여부 (만들 수 있다면 사용한 원소의 개수, 없다면 -1)
    vector<vector<int>> dp(31, vector<int>(ans + 1, -1));
    for (int i = 0; i <= 30; i++) dp[i][0] = 0;
    for (int i = 2; i <= 30; i++) {
        for (int j = 0; j <= ans; j++) {
            dp[i][j] = dp[i - 1][j];
            if (j - pcnt[i] >= 0 && dp[i][j - pcnt[i]] != -1) {
                int cand = dp[i][j - pcnt[i]] + i;
                if (cand <= n) {
                    if (dp[i][j] == -1 || cand < dp[i][j]) dp[i][j] = cand;  // -1 처리 + 최소값 유지
                }
            }
        }
    }

    if (dp[30][ans] == -1 || dp[30][ans] > n) {
        cout << 0 << '\n';
        return;
    }

    // 역추적
    int cur = ans;
    vector<int> used(31, 0);
    for (int i = 30; i >= 2; i--) {
        if (dp[i][cur] == dp[i - 1][cur]) continue; // i 안 쓰기
        while (cur - pcnt[i] >= 0 && dp[i][cur - pcnt[i]] != -1 && dp[i][cur] == dp[i][cur - pcnt[i]] + i) { // i 필요한 만큼 쓰기
            used[i]++;
            cur -= pcnt[i];
        }
    }

    int tmp = n;
    for (int i = 2; i <= 30; i++) {
        while (used[i]--) {
            for (int j = tmp - i + 1; j <= tmp; j++) cout << j << ' ';
            tmp -= i;
        }
    }
    for (int i = tmp; i > 0; i--) cout << i << ' '; // 나머지는 내림차순
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;

    pcnt = vector<int>(31, 0);
    for (int i = 2; i <= 30; i++) pcnt[i] = i * (i - 1) / 2;

    for (int i = 0; i < T; i++) {
        solve();
    }
}