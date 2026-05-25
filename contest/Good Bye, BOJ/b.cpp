#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve() {
    int n;
    cin >> n;

    bool psb = true;
    ll time = 0;
    ll cura = 0;
    ll curb = 0;
    ll curc = 0;

    for (int i = 0; i < n; i++) {
        ll a, b, c, p;
        cin >> a >> b >> c >> p;

        ll tmp = max(0LL, a - cura) + max(0LL, b - curb) + max(0LL, c - curc);
        if (tmp < max(0LL, p - time)) {
            cura = max(a, cura);
            curb = max(b, curb);
            curc = max(c, curc);
            time += tmp;
            time++;
        } else {
            psb = false;
        }
    }

    if (psb) cout << "YES\n";
    else cout << "NO\n";
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