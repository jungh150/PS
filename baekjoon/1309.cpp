#include <iostream>
#include <vector>
using namespace std;

int mod = 9901;

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> a(n + 1, vector<int>(3, 0));
    // 0: 둘 다 배치 X, 1: 왼쪽에만 배치, 2: 오른쪽에만 배치

    a[0][0] = 1;
    a[1][0] = 1;
    a[1][1] = 1;
    a[1][2] = 1;

    for (int i = 2; i < n + 1; i++) {
        a[i][0] = (a[i - 1][0] + a[i - 1][1] + a[i - 1][2]) % mod;
        a[i][1] = (a[i - 1][0] + a[i - 1][2]) % mod;
        a[i][2] = (a[i - 1][0] + a[i - 1][1]) % mod;
    }

    cout << (a[n][0] + a[n][1] + a[n][2]) % mod << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}