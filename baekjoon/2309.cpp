#include <iostream>
#include <algorithm>
using namespace std;

int a[9];
bool chk[9];
bool fin = false;

void dfs(int idx, int cnt, int sumt) {
    if (fin) return;
    if (cnt == 7) {
        if (sumt != 100) return;
        for (int i = 0; i < 9; i++) {
            if (chk[i]) cout << a[i] << '\n';
        }
        fin = true;
        return;
    } else if (cnt < 7) {
        if (sumt >= 100) return;
        for (int i = idx; i < idx + 3; i++) {
            if (i < 9) {
                chk[i] = true;
                dfs(i + 1, cnt + 1, sumt + a[i]);
                chk[i] = false;
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 0; i < 9; i++) cin >> a[i];
    sort(a, a + 9);

    dfs(0, 0, 0);
}