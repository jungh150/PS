#include <iostream>
#include <vector>
using namespace std;

long long fact(int x) {
    if (x == 0) return 1;
    else return x * fact(x - 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> comb(n + m, vector<int>(n + m, 1));
    for (int i = 1; i < n + m; i++) {
        for (int j = 1; j < i; j++) {
            comb[i][j] = comb[i - 1][j - 1] + comb[i - 1][j];
        }
    }

    long long ans = 0;
    if (k == 0) {
        ans = comb[n + m - 2][n - 1];
    } else {
        int i = (k - 1) / m;
        int j = (k - 1) % m;
        ans = comb[i + j][i] * comb[n + m - i - j - 2][n - i - 1];
    }

    cout << ans << '\n';
}