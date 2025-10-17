#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    auto q = [&](int x, int l, int r) {
        cout << x << " " << l << " " << r << endl;
        long long res;
        cin >> res;
        return res;
    };

    int l = 1;
    int r = n;
    long long totalp = q(1, l, r);
    long long totala = q(2, l, r);
    while (l < r) {
        int m = (l + r) / 2;
        long long lp = q(1, l, m);
        long long la = q(2, l, m);
        long long rp = totalp - lp;
        long long ra = totala - la;

        if (lp != la && rp != ra) {
            long long lcnt = la - lp;
            long long rcnt = ra - rp;
            long long lans = m - lcnt + 1;
            long long rans = (m + 1) + rcnt - 1;
            cout << "! " << lans << " " << rans << endl;
            return;
        } else if (lp == la) {
            l = m + 1;
            totalp = rp;
            totala = ra;
        } else if (rp == ra) {
            r = m;
            totalp = lp;
            totala = la;
        }
    }
    cout << "! " << l << " " << r << endl;
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