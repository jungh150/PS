#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int l, n, t;
    cin >> l >> n >> t;

    vector<int> pos(n);
    vector<int> dir(n);
    for (int i = 0; i < n; i++) {
        cin >> pos[i];
        char c;
        cin >> c;
        if (c == 'R') dir[i] = 1;
        else dir[i] = -1;
    }

    int cnt = 0;

    for (int i = 1; i <= t; i++) {
        for (int j = 0; j < n; j++) {
            pos[j] += dir[j];
            if (pos[j] == 0) dir[j] = -dir[j];
            else if (pos[j] == l) dir[j] = -dir[j];
        }
        for (int j = 0; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                if (pos[j] == pos[k]) {
                    dir[j] = -dir[j];
                    dir[k] = -dir[k];
                    cnt++;
                }
            }
        }
    }

    cout << cnt << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}