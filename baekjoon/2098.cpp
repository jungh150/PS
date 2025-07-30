#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int MAXVAL = 1e9;
int n;
vector<vector<int>> w;
vector<vector<int>> dp;

int td(int cur, int vst) {
    if (dp[cur][vst] != -1) return dp[cur][vst];

    if (vst == (1 << n) - 1) { // 모든 도시를 방문했으면 다시 돌아와야 함
        if (w[cur][0] > 0) return w[cur][0];
        else return MAXVAL;
    }

    dp[cur][vst] = MAXVAL;
    for (int nxt = 0; nxt < n; nxt++) {
        // 방문한 적 없고, 갈 수 있는 정점이라면
        if (!(vst & (1 << nxt)) && (w[cur][nxt] > 0)) {
            dp[cur][vst] = min(dp[cur][vst], w[cur][nxt] + td(nxt, vst | (1 << nxt)));
        }
    }

    return dp[cur][vst];
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    w = vector<vector<int>>(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> w[i][j];
        }
    }
    
    dp = vector<vector<int>>(n, vector<int>(1 << n, -1));
    
    // 시작 도시는 임의로 0번 도시로 지정
    cout << td(0, 1) << '\n';
}