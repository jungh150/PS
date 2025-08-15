#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<vector<int>> a;
vector<bool> vst;

int td(int cur) {
    if (a[cur].empty()) return 1;
    vector<int> tmp;
    for (int nxt: a[cur]) {
        tmp.push_back(td(nxt));
    }
    sort(tmp.begin(), tmp.end(), greater<>());
    int maxt = 0;
    for (int i = 0; i < tmp.size(); i++) {
        maxt = max(maxt, tmp[i] + i);
    }
    return maxt + 1;
}

void solve() {
    cin >> n;
    a = vector<vector<int>>(n);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (x == -1) continue;
        a[x].push_back(i);
    }

    cout << td(0) - 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}