#include <iostream>
#include <map>
using namespace std;

map<string, int> m;

void f(string s, int idx, string res, int cnt) {
    if (cnt == 0) {
        if (m.count(res)) m[res]++;
        else m[res] = 1;
        return;
    }
    for (int i = idx; i <= s.size() -  cnt; i++) {
        f(s, i + 1, res + s[i], cnt - 1);
    }
}

void solve() {
    string x, y, z;
    int k;
    cin >> x >> y >> z >> k;

    f(x, 0, "", k);
    f(y, 0, "", k);
    f(z, 0, "", k);

    bool flag = false;
    for (auto it = m.begin(); it != m.end(); it++) {
        if (it->second >= 2) {
            cout << it->first << '\n';
            flag = true;
        }
    }
    if (!flag) cout << "-1\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}