#include <bits/stdc++.h>
using namespace std;

void solve() {
    long long k, x;
    cin >> k >> x;

    long long tmp = x;
    while (tmp % 2 == 0) tmp /= 2;
    
    vector<int> anst;
    for (int i = 1; i <= 60; i++) {
        if (tmp < (1LL << i)) break;

        if (tmp & (1LL << i)) anst.push_back(2);
        else anst.push_back(1);
    }
    // for (int i = 1; i <= 60; i++) {
    //     if ((tmp >> i) < 1) break;

    //     if ((tmp >> i) & 1) anst.push_back(2);
    //     else anst.push_back(1);
    // }

    long long a = (1LL << k);
    long long b = a;

    for (int an: anst) {
        if (an == 1) {
            b += (a / 2);
            a /= 2;
        } else if (an == 2) {
            a += (b / 2);
            b /= 2;
        }
    }

    bool rev = false;
    if (b % x == 0) rev = true;

    vector<int> ans;

    if (rev) {
        for (int an: anst) {
            if (an == 1) ans.push_back(2);
            else if (an == 2) ans.push_back(1);
        }
        swap(a, b);
    } else {
        for (int an: anst) {
            ans.push_back(an);
        }
    }
    
    while (a != x) {
        a /= 2;
        ans.push_back(1);
    }

    cout << ans.size() << '\n';
    for (int an: ans) cout << an << ' ';
    cout << '\n';
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