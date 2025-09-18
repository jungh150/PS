#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int l, w, n;
    cin >> l >> w >> n;

    if ((l * w) % n != 0) {
        cout << "impossible\n";
        return;
    }
    
    int k = l * w / n;

    vector<int> div; // k의 약수
    for (int i = 1; i * i <= k; i++) {
        if (k % i == 0) {
            div.push_back(i);
            if (i != (k / i)) div.push_back(k / i);
        }
    }

    int igap = -1;
    int jgap = -1;
    for (int x: div) {
        int y = k / x;
        if (l % x == 0 && w % y == 0) {
            igap = x;
            jgap = y;
            break;
        }
    }

    if (igap == -1 || jgap == -1) {
        cout << "impossible\n";
        return;
    }

    vector<vector<char>> ans(l, vector<char>(w));
    int icnt = l / igap;
    int jcnt = w / jgap;
    int cur = 0;
    for (int i = 0; i < icnt; i++) {
        for (int j = 0; j < jcnt; j++) {
            for (int ii = 0; ii < igap; ii++) {
                for (int jj = 0; jj < jgap; jj++) {
                    ans[i * igap + ii][j * jgap + jj] = 'A' + cur;
                }
            }
            cur++;
        }
    }

    for (int i = 0; i < l; i++) {
        for (int j = 0; j < w; j++) {
            cout << ans[i][j];
        }
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    // cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}