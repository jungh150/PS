#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    s += 'T';

    bool three = false;
    bool overfive = false;
    int fourcnt = 0;
    int totalcnt = 0;
    int cnt = 0;
    for (int i = 0; i < n + 1; i++) {
        if (s[i] == 'H') {
            cnt++;
            totalcnt++;
        } else if (s[i] == 'T') {
            if (cnt == 3) three = true;
            else if (cnt == 4) fourcnt++;
            else if (cnt >= 5) overfive = true;
            cnt = 0;
        }
    }

    totalcnt -= fourcnt;

    if (three || overfive) {
        cout << "First\n";
    } else {
        if (totalcnt % 2 == 1) cout << "First\n";
        else cout << "Second\n";
    }
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