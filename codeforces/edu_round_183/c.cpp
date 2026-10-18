#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    int acnt = 0;
    int bcnt = 0;
    for (char c: s) {
        if (c == 'a') acnt++;
        else if (c == 'b') bcnt++;
    }
    
    if (acnt == bcnt) {
        cout << 0 << '\n';
        return;
    }

    if (acnt == 0 || bcnt == 0) {
        cout << -1 << '\n';
        return;
    }

    int cnt = acnt - bcnt;

    int offset = n;
    vector<int> idx(2 * n + 1, -1); // idx[x]: prefix sum이 (x - offset)인 가장 큰 인덱스
    
    int ans = 1e8;
    int tmp = 0;
    idx[0 + offset] = 0;
    for (int i = 0; i < n; i++) {
        // 현재 prefix 값인 tmp 계산
        if (s[i] == 'a') tmp++;
        else if (s[i] == 'b') tmp--;

        // idx 갱신
        idx[tmp + offset] = i + 1;
        // cout << tmp << '\n';

        // 구간 합이 cnt와 동일해지는 구간 길이 찾기
        int curidx = idx[(tmp - cnt) + offset];
        // cout << tmp - cnt << '\n';
        // cout << curidx << '\n';
        if (curidx != -1) {
            ans = min(ans, (i + 1) - curidx);
        }
    }

    if (ans == 1e8 || ans == n) cout << -1 << '\n';
    else cout << ans << '\n';
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