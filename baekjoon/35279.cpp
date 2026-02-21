#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve() {
    int b, k;
    cin >> b >> k;

    vector<ll> pow;
    ll tmp = 1;
    for (int i = 0; i < 64; i++) {
        if (tmp <= 0) break;
        pow.push_back(tmp);
        tmp *= b;
    }
    int sz = pow.size();

    priority_queue<ll, vector<ll>, greater<>> pq;
    set<ll> ans;

    for (int i = 1; i < b; i++) pq.push(i);

    while (ans.size() < k) {
        ll x = pq.top();
        pq.pop();
        if (ans.count(x)) continue;
        ans.insert(x);
        for (int i = 2; i < sz; i++) {
            tmp = x * i;
            if (tmp / pow[i - 1] > 0 && tmp / pow[i] == 0) pq.push(tmp);
        }
    }

    for (auto it = ans.begin(); it != ans.end(); it++) cout << *it << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}