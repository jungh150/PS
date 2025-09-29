#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, h, w;
    cin >> n >> h >> w;

    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        
        if ((c == 'Y') || (c == 'N' && w == 0)) {
            cout << "Y ";
            h--;
            w++;
        } else {
            cout << "N ";
        }

        cin >> c;

        if ((c == 'Y') || (c == 'N' && h == 0)) {
            cout << "Y\n";
            w--;
            h++;
        } else {
            cout << "N\n";
        }
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