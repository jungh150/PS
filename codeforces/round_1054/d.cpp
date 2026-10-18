#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector<long long> acnt(n + 1, 0);
    vector<long long> bcnt(n + 1, 0);
    vector<long long> aps(n + 1, 0); // 인덱스 누적합
    vector<long long> bps(n + 1, 0); // 인덱스 누적합

    if (n <= 3) {
        cout << 0 << '\n';
        return;
    }

    for (int i = 1; i < n + 1; i++) {
        if (s[i - 1] == 'a') {
            acnt[i] = acnt[i - 1] + 1;
            bcnt[i] = bcnt[i - 1];
            aps[i] = aps[i - 1] + i;
            bps[i] = bps[i - 1];
        } else if (s[i - 1] == 'b') {
            acnt[i] = acnt[i - 1];
            bcnt[i] = bcnt[i - 1] + 1;
            aps[i] = aps[i - 1];
            bps[i] = bps[i - 1] + i;
        }
    }

    long long ans = 1e12;
    for (int i = 1; i < n + 1; i++) {
        long long tmp = 0;
        if (s[i - 1] == 'a') {
            long long cnt1 = acnt[i - 1] - acnt[0];
            tmp += i * cnt1 - (aps[i - 1] - aps[0]) - (cnt1 * (cnt1 + 1) / 2); // left
            long long cnt2 = acnt[n] - acnt[i];
            tmp += (aps[n] - aps[i]) - i * cnt2 - (cnt2 * (cnt2 + 1) / 2); // right
        } else if (s[i - 1] == 'b') {
            long long cnt1 = bcnt[i - 1] - bcnt[0];
            tmp += i * cnt1 - (bps[i - 1] - bps[0]) - (cnt1 * (cnt1 + 1) / 2); // left
            long long cnt2 = bcnt[n] - bcnt[i];
            tmp += (bps[n] - bps[i]) - i * cnt2 - (cnt2 * (cnt2 + 1) / 2); // right
        }
        // cout << "i " << i << "  tmp " << tmp << '\n'; 
        ans = min(ans, tmp);
    }

    cout << ans << '\n';
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