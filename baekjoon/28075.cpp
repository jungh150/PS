#include <iostream>
#include <vector>
using namespace std;

int task[2][3];
int n, m, ans;

void dfs(int idx, int tmp, int pre) {
    if (idx == n) {
        if (tmp >= m) ans++;
        return;
    }
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            if (pre == j) dfs(idx + 1, tmp + task[i][j] / 2, j);
            else dfs(idx + 1, tmp + task[i][j], j);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> task[i][j];
        }
    }
    
    dfs(0, 0, -1);

    cout << ans << '\n';
}