#include <iostream>
#include <vector>
using namespace std;

// dp[a][b][c][d]: (T의 누적합 % 3)이 a개, (G의 누적합 % 3)이 b개, (F의 누적합 % 3)이 c개, (P의 누적합 % 3)이 d개인 인덱스 개수
int dp[3][3][3][3];
int cnt[4];

void solve(){
    int n;
    cin >> n;
    string s;
    cin >> s;

    // 맨 처음부터 구간으로 보는 경우 처리
    dp[0][0][0][0]++;

    long long ans = 0;
    for (char c: s) {
        if (c == 'T') cnt[0] = (cnt[0] + 1) % 3;
        else if (c == 'G') cnt[1] = (cnt[1] + 1) % 3;
        else if (c == 'F') cnt[2] = (cnt[2] + 1) % 3;
        else if (c == 'P') cnt[3] = (cnt[3] + 1) % 3;
        // 현재 기준 늘어나는 흥미로운 구간 수 = 현재 인덱스와 4가지 종류의 누적합들의 나머지가 전부 동일한 인덱스의 개수
        ans += dp[cnt[0]][cnt[1]][cnt[2]][cnt[3]];
        dp[cnt[0]][cnt[1]][cnt[2]][cnt[3]]++;
    }

    cout << ans << '\n';
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}