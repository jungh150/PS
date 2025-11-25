#include <iostream>
#include <vector>
using namespace std;

void solve() {
    string s;
    int n;
    cin >> s >> n;

    vector<int> a(52);
    for (int i = 0; i < 52; i++) a[i] = i;

    vector<int> str;
    for (char c: s) {
        if ('a' <= c && c <= 'z') str.push_back(c - 'a');
        else str.push_back(c - 'A' + 26);
    }

    while (n--) {
        int q;
        char c1, c2;
        cin >> q;

        if (q == 1) {
            cin >> c1 >> c2;
            int idx1, idx2;

            if ('a' <= c1 && c1 <= 'z') idx1 = c1 - 'a';
            else idx1 = c1 - 'A' + 26;

            if ('a' <= c2 && c2 <= 'z') idx2 = c2 - 'a';
            else idx2 = c2 - 'A' + 26;

            for (int i = 0; i < 52; i++) {
                if (a[i] == idx1) a[i] = idx2;
            }
        } else if (q == 2) {
            for (int x: str) {
                if (a[x] < 26) cout << (char) ('a' + a[x]);
                else cout << (char) ('A' + a[x] - 26);
            }
            cout << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}