#include <iostream>
#include <vector>
using namespace std;

int q, a, b, k, tar;
vector<vector<int>> dp;

int td(int cur, int chk) {
    if (dp[cur][chk] != -1) return dp[cur][chk];

    // 상대를 지게 만드는 내 선택이 하나라도 존재하면 내가 승
    for (int x = 1; x < k + 1; x++) { // 내가 이번 턴에 사용할 카드 x
        if (chk & (1 << (x - 1))) { // 사용할 수 있는 카드면
            if (cur - x <= 0) return dp[cur][chk] = 1; // 바로 승리
            if (td(cur - x, chk - (1 << (x - 1))) == 0) return dp[cur][chk] = 1;
        }
    }

    return dp[cur][chk] = 0;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> q;

    // dp[cur][chk]: 지금까지 더해진 수가 cur이고 사용할 수 있는 카드가 chk(비트마스킹)일 때, 승패 여부 (1:승/0:패)
    dp = vector<vector<int>>(56, vector<int>(1 << 10, -1));
    
    while (q--) {
        cin >> a >> b >> k;
        tar = b - a;

        int sumt = k * (k + 1) / 2;
        int cnt = tar / sumt;

        if (tar % sumt == 0) cnt--;
        tar -= sumt * cnt;

        // dp[cur][chk]: 지금까지 더해진 수가 cur이고 사용할 수 있는 카드가 chk(비트마스킹)일 때, 승패 여부 (1:승/0:패)
        // dp = vector<vector<int>>(sumt + 1, vector<int>(1 << k, -1));

        int win = td(tar, (1 << k) - 1);
        if ((k * cnt) % 2 == 1) win = 1 - win;

        if (win == 1) cout << "swoon\n";
        else cout << "raararaara\n";
    }
}