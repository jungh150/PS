#include <bits/stdc++.h>
using namespace std;

int gcd(int x, int y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}

void solve() {
    int w, l;
    cin >> w >> l;

    set<int> ans;
    ans.insert(1);
    ans.insert(2);

    int tmp = gcd(w, l - 2);
    // cout << tmp << '\n';
    for (int i = 1; i * i <= tmp; i++) {
        if (tmp % i == 0) {
            ans.insert(i);
            ans.insert(tmp / i);
        }
    }

    tmp = gcd(w - 1, l - 1);
    // cout << tmp << '\n';
    for (int i = 1; i * i <= tmp; i++) {
        if (tmp % i == 0) {
            ans.insert(i);
            ans.insert(tmp / i);
        }
    }

    tmp = gcd(w - 2, l);
    // cout << tmp << '\n';
    for (int i = 1; i * i <= tmp; i++) {
        if (tmp % i == 0) {
            ans.insert(i);
            ans.insert(tmp / i);
        }
    }

    cout << ans.size() << ' ';
    for (auto it = ans.begin(); it != ans.end(); it++) cout << *it << ' ';
    cout << '\n';
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