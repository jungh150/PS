#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

void solve() {
    int n;
    cin >> n;

    set<string> s;
    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        s.insert(str);
        reverse(str.begin(), str.end());
        if (s.count(str)) {
            int sz = str.size();
            cout << sz << ' ' << str[(sz - 1) / 2] << '\n';
            return;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}