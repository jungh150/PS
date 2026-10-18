#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    vector<int> ice(m);
    for (int i = 0; i < m; i++) cin >> ice[i];

    sort(ice.begin(), ice.end());

    map<long long, long long> mp;
    for (int i = 0; i < n; i++) {
        long long house = i * 100;
        int idx = upper_bound(ice.begin(), ice.end(), house) - ice.begin();

        long long minv;
        if (idx == m) minv = abs(house - ice[idx - 1]);
        else if (idx == 0) minv = abs(house - ice[idx]);
        else minv = min(abs(house - ice[idx]), abs(house - ice[idx - 1]));

        if (!mp.count(2 * (house - minv) + 1)) mp[2 * (house - minv) + 1] = p[i];
        else mp[2 * (house - minv) + 1] += p[i];

        if (!mp.count(2 * (house + minv))) mp[2 * (house + minv)] = -p[i];
        else mp[2 * (house + minv)] -= p[i];
    }

    long long ans = 0;
    long long tmp = 0;
    for (auto it = mp.begin(); it != mp.end(); it++) {
        tmp += it->second;
        ans = max(ans, tmp);
    }

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