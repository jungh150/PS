#include <iostream>
#include <stack>
using namespace std;

void solve() {
    int n;
    cin >> n;

    int ans = 0;

    while (n--) {
        string s;
        cin >> s;

        stack<char> stk;

        for (char c: s) {
            if (!stk.empty() && stk.top() == c) stk.pop();
            else stk.push(c);
        }

        if (stk.empty()) ans++;
    }

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}