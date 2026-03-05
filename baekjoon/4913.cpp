#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n = 1000000;
    vector<bool> p(n + 1, 1);
    p[0] = p[1] = 0;

    for (int i = 2; i * i < n + 1; i++) {
        if (!p[i]) continue;
        for (int j = i * i; j < n + 1; j += i) p[j] = 0;
    }

    vector<int> ps1(n + 1, 0);
    vector<int> ps2(n + 1, 0);

    for (int i = 1; i < n + 1; i++) {
        if (p[i]) {
            ps1[i] = ps1[i - 1] + 1;
            if (i == 2 || i % 4 == 1) ps2[i] = ps2[i - 1] + 1;
            else ps2[i] = ps2[i - 1];
        } else {
            ps1[i] = ps1[i - 1];
            ps2[i] = ps2[i - 1];
        }
    }

    while (1) {
        int l, u;
        cin >> l >> u;
        if (l == -1 && u == -1) return;
        
        int ll = l;
        int uu = u;
        if (l <= 0) ll = 1;
        if (u <= 0) uu = 1;

        cout << l << ' ' << u << ' ' << ps1[uu] - ps1[ll - 1] << ' ' << ps2[uu] - ps2[ll - 1] << '\n';
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