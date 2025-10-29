#include <iostream>
using namespace std;

void solve() {
    string korea = "KOREA";
    string s;
    cin >> s;

    int cnt = s.size();
    int idx = 0;
    for (char c: s) {
        if (c == korea[idx]) {
            idx++;
            if (idx >= 5) idx = 0;
        } else {
            cnt--;
        }
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