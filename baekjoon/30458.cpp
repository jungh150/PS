#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    string s;
    cin >> n >> s;

    vector<int> cnt(26, 0);

    for (int i = 0; i < n; i++) cnt[s[i] - 'a']++;

    if (n % 2 == 0) {
        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2 == 1) {
                cout << "No\n";
                return;
            }
        }
    } else {
        int idx = -1;
        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2 == 1) {
                if (idx != -1) {
                    cout << "No\n";
                    return;
                } else {
                    idx = i;
                }
            }
        }
        if (idx != s[n / 2] - 'a') {
            cout << "No\n";
            return;
        }
    }
    cout << "Yes\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}