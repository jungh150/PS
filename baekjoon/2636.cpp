#include <iostream>
using namespace std;

void solve() {
    int n;
    cin >> n;

    int maxc = 0;
    int maxsec = 0;

    for (int i = 1; i <= n; i++) {
        int pre = n;
        int cur = i;
        int cnt = 2;

        while (1) {
            int nxt = pre - cur;
            if (nxt < 0) break;
            cnt++;
            pre = cur;
            cur = nxt;
        }

        if (cnt > maxc) {
            maxc = cnt;
            maxsec = i;
        }
    }

    int pre = n;
    int cur = maxsec;
    cout << maxc << '\n';
    cout << pre << ' ' << cur << ' ';
    while (1) {
        int nxt = pre - cur;
        if (nxt < 0) break;
        cout << nxt << ' ';
        pre = cur;
        cur = nxt;
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}