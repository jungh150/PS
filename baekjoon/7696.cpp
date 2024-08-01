#include <iostream>
#include <vector>
using namespace std;

vector<bool> chk;
int cnt, n, ans;
bool isfin;

void dfs(int idx, int res, int fin) {
    if (idx == fin) {
        cnt++;
        if (cnt == n) {
            isfin = true;
            ans = res;
        }
        return;
    }
    if (idx == 0) {
        for (int i = 1; i < 10; i++) {
            if (!chk[i]) {
                chk[i] = true;
                dfs(idx + 1, res * 10 + i, fin);
                chk[i] = false;
            }
            if (isfin) break;
        }
    } else {
        for (int i = 0; i < 10; i++) {
            if (!chk[i]) {
                chk[i] = true;
                dfs(idx + 1, res * 10 + i, fin);
                chk[i] = false;
            }
            if (isfin) break;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    while (true) {
        cin >> n;
        if (n == 0) break;

        isfin = false;
        cnt = 0;
        ans = 0;
        for (int i = 1; i <= 10; i++) {
            chk = vector<bool>(10, false);
            dfs(0, 0, i);
            if (isfin) break;
        }

        cout << ans << '\n';
    }
}