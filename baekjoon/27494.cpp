#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string ans = "2023";

    int cnt = 0;
    for (int i = 2023; i <= n; i++) {
        string s = to_string(i);
        int idx = 0;
        for (char c: s) {
            if (c == ans[idx]) idx++;
        }
        if (idx == 4) cnt++;
    }

    cout << cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}