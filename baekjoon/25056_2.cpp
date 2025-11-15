#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> p(n);
    for (int i = 0; i < n; i++) cin >> p[i];

    vector<int> ice(m);
    for (int i = 0; i < m; i++) cin >> ice[i];

    sort(ice.begin(), ice.end());

    vector<vector<int>> sec;
    for (int i = 0; i < n; i++) {
        int house = i * 100;
        int idx = upper_bound(ice.begin(), ice.end(), house) - ice.begin();

        int minv;
        if (idx == m) minv = abs(house - ice[idx - 1]);
        else if (idx == 0) minv = abs(house - ice[idx]);
        else minv = min(abs(house - ice[idx]), abs(house - ice[idx - 1]));

        sec.push_back({house - minv, house + minv, p[i]});
    }

    sort(sec.begin(), sec.end());

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq; // {e, val}

    ll ans = 0;
    ll tmp = 0;
    for (int i = 0; i < n; i++) {
        int s = sec[i][0];
        int e = sec[i][1];
        int val = sec[i][2];
        while (!pq.empty() && pq.top().first <= s) {
            tmp -= pq.top().second;
            pq.pop();
        }
        if (s == e) continue;
        tmp += val;
        pq.emplace(e, val);
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