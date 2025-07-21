#include <iostream>
#include <vector>
using namespace std;

int MOD = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int l, n, m;
    cin >> l;

    vector<bool> a1(l - 1);
    int idx = 0;

    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        for (int j = 0; j < x - 1; j++) {
            a1[idx++] = false;
        }
        a1[idx++] = true;
    }

    vector<bool> a2(l - 1);
    idx = 0;

    cin >> m;
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        for (int j = 0; j < x - 1; j++) {
            a2[idx++] = false;
        }
        a2[idx++] = true;
    }

    // for (int i = 0; i < l - 1; i++) {
    //     if (a1[i]) cout << 1 << ' ';
    //     else cout << 0 << ' ';
    // }
    // cout << '\n';

    // for (int i = 0; i < l - 1; i++) {
    //     if (a2[i]) cout << 1 << ' ';
    //     else cout << 0 << ' ';
    // }
    // cout << '\n';

    int ans1 = 0;
    for (int i = 0; i < l - 1; i++) {
        if (a1[i] != a2[i]) ans1++;
    }

    int ans2 = 0;
}