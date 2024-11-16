#include <iostream>
#include <vector>
using namespace std;

int n;
vector<vector<char>> ans;

void recur(int si, int ni, int sj, int nj) {
    if (ni == 3) {
        ans[si][sj + 2] = '*';
        ans[si + 1][sj + 1] = '*';
        ans[si + 1][sj + 3] = '*';
        ans[si + 2][sj] = '*';
        ans[si + 2][sj + 1] = '*';
        ans[si + 2][sj + 2] = '*';
        ans[si + 2][sj + 3] = '*';
        ans[si + 2][sj + 4] = '*';
        return;
    }
    recur(si, ni / 2, sj + nj / 4 + 1, nj / 2);
    recur(si + ni / 2, ni / 2, sj, nj / 2);
    recur(si + ni / 2, ni / 2, sj + nj / 2 + 1, nj / 2);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    ans = vector<vector<char>>(n, vector<char>(2 * n - 1, ' '));
    recur(0, n, 0, 2 * n - 1);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * n - 1; j++) {
            cout << ans[i][j];
        }
        cout << '\n';
    }
}