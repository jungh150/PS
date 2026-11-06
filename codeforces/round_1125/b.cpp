#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    string s;
    cin >> n >> s;

    vector<bool> a(n + 1, 0);
    stack<int> stk;
    int total = n;

    for (int i = 1; i < n + 1; i++) {
        if (s[i - 1] == '1') {
            stk.push(i);
        } else if (s[i - 1] == '2') {
            if (!stk.empty()) {
                a[stk.top()] = 1;
                total--;
                stk.pop();
            } else {
                a[i] = 1;
                total--;
            }
        } else if (s[i - 1] == '3') {
            a[i] = 1;
            total--;
        }
    }

    cout << total << '\n';
    for (int i = 1; i < n + 1; i++) {
        if (!a[i]) cout << i << ' ';
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}