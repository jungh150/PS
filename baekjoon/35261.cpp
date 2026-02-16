#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    string s;
    cin >> n >> s;

    string str = "eagle";
    int minc = 5;
    for (int i = 0; i <= n - 5; i++) {
        int cnt = 0;
        for (int j = 0; j < 5; j++) {
            if (s[i + j] != str[j]) cnt++;
        }
        minc = min(minc, cnt);
    }

    cout << minc << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}