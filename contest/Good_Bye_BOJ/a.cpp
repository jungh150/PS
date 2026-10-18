#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<string> ans1(2 * n, "");
    vector<string> ans2(n, "");

    for (int i = 0; i < 2 * n; i++) {
        for (int j = 0; j < 2 * n - i - 1; j++) ans1[i] += ' ';
        ans1[i] += '*';
        for (int j = 0; j < i; j++) ans1[i] += ' ';
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - i - 1; j++) ans2[i] += ' ';
        ans2[i] += '*';
        for (int j = 0; j < i; j++) ans2[i] += ' ';
        ans2[i] += ' ';
        for (int j = 0; j < i; j++) ans2[i] += ' ';
        ans2[i] += '*';
        for (int j = 0; j < n - i - 1; j++) ans2[i] += ' ';
    }

    for (int i = 0; i < n; i++) cout << ans1[i] << ' ' << ans2[i] << '\n';
    for (int i = 0; i < n; i++) cout << ans1[n + i] << ' ' << ans2[n - i - 1] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}