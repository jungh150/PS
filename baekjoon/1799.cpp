#include <iostream>
#include <vector>
using namespace std;

int n, ans;
vector<vector<int>> a;

bool promising(int ci, int cj) {
    int csum = ci + cj;
    for (int i = 0; i < n; i++) {
        int j = csum - i;
        if ((j < 0) || (j > n - 1)) continue;
        if (a[i][j] == 2) return false;
    }
    int cdif = cj - ci;
    for (int i = 0; i < n; i++) {
        int j = i + cdif;
        if ((j < 0) || (j > n - 1)) continue;
        if (a[i][j] == 2) return false;
    }
    return true;
}

// 합이 0 ~ (2n - 2)인 우상향 대각선 사용
void bt(int idx, int cnt) {
    if (idx == 2 * n - 1) {
        ans = max(ans, cnt);
        return;
    }
    for (int i = 0; i < n; i++) {
        int j = idx - i;
        if ((j < 0) || (j > n - 1)) continue;
        if (a[i][j] == 0) continue;
        if (promising(i, j)) {
            a[i][j] = 2;
            bt(idx + 1, cnt + 1);
            a[i][j] = 1;
        }
    }
    bt(idx + 1, cnt);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    a = vector<vector<int>>(n, vector<int>(n));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    bt(0, 0);

    cout << ans << '\n';
}