#include <bits/stdc++.h>
using namespace std;

void solve() {
    int num = 500001;
    vector<bool> p(num, 1);
    p[0] = p[1] = 0;

    for (int i = 2; i * i <= num; i++) {
        if (p[i]) {
            for (int j = i * i; j < num; j += i) {
                p[j] = 0;
            }
        }
    }

    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    vector<int> dif(n + 2, 0);
    while (m--) {
        int s, e;
        cin >> s >> e;
        dif[s] += 1;
        dif[e + 1] -= 1;
    }

    vector<int> ps(n + 1, 0);
    for (int i = 1; i < n + 1; i++) {
        ps[i] = ps[i - 1] + dif[i];
    }

    double ans = 0;
    for (int i = 1; i < n + 1; i++) {
        if (ps[i] > 0) {
            long long sumt = 0;
            int cnt = 0;
            int tmp = a[i];
            for (int j = 2; j * j <= tmp; j++) {
                if (p[j] == 1 && tmp % j == 0) {
                    sumt += j;
                    cnt++;
                }
                while (tmp % j == 0) tmp /= j;
            }
            if (tmp > 1) {
                sumt += tmp;
                cnt++;
            }
            ans += (double) sumt / cnt;
        } else {
            ans += a[i];
        }
    }

    cout << fixed;
    cout.precision(12);
    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}