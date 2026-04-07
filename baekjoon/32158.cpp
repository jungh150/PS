#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    string s;
    cin >> n >> s;

    vector<bool> used(n, false);

    for (int i = 0; i < n; i++) {
        if (s[i] == 'P' && !used[i]) {
            for (int j = 0; j < n; j++) {
                if (s[j] == 'C' && !used[j]) {
                    s[i] = 'C';
                    s[j] = 'P';
                    used[i] = used[j] = true;
                    break;
                }
            }
        }
    }

    cout << s << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}