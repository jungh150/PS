#include <iostream>
using namespace std;

int a[5];
bool chk[5];
int sub[3];
int mina = 1000000000;

int gcd(int x, int y) {
    if (y == 0) return x;
    return gcd (y, x % y);
}

void dfs(int idx, int cnt) {
    if (cnt == 3) {
        int tmp = sub[0] * sub[1] / gcd(sub[0], sub[1]);
        int ans = tmp * sub[2] / gcd(tmp, sub[2]);
        mina = min(mina, ans);
    }

    for (int i = idx; i < 5; i++) {
        if (!chk[i]) {
            chk[i] = true;
            sub[cnt] = a[i];
            dfs(i + 1, cnt + 1);
            chk[i] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 0; i < 5; i++) cin >> a[i];
    dfs(0, 0);

    cout << mina << '\n';
}