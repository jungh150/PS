#include <iostream>
using namespace std;

void solve() {
    int n;
    string s;
    cin >> n >> s;

    for (int i = 0; i < n; i++) {
        bool flag = true;
        for (int j = i + 1; j < i + 5; j++) {
            if (s[j] != s[j - 1] - 1 && s[j] != s[j - 1] + 1) {
                flag = false;
                break;
            }
        }
        if (flag) {
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