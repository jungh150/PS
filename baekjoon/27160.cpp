#include <iostream>
#include <map>
using namespace std;

void solve() {
    int n;
    cin >> n;

    map<string, int> fr;
    for (int i = 0; i < n; i++) {
        string s;
        int x;
        cin >> s >> x;
        if (fr.count(s)) fr[s] += x;
        else fr[s] = x;
    }

    for (auto it = fr.begin(); it != fr.end(); it++) {
        if (it->second == 5) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}