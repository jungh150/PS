#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    map<string, int> mp;
    for (int i = 0; i < n; i++) {
        string s;
        int p;
        cin >> s >> p;
        mp[s] = p;
    }

    int score = 0;
    for (int i = 0; i < k; i++) {
        string s;
        cin >> s;
        score += mp[s];
        mp.erase(s);
        m--;
    }

    vector<int> rest;
    for (auto it = mp.begin(); it != mp.end(); it++) {
        rest.push_back(it->second);
    }

    sort(rest.begin(), rest.end());

    int sz = rest.size();
    int tmp1 = 0;
    for (int i = 0; i < m; i++) tmp1 += rest[i];
    int tmp2 = 0;
    for (int i = sz - 1; i > sz - m - 1; i--) tmp2 += rest[i];

    cout << score + tmp1 << ' ' << score + tmp2 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}