#include <iostream>
#include <vector>
#include <set>
using namespace std;

int n;
vector<int> col;
int cnt = 0;

bool promising(int idx) {
    for (int k = 0; k < idx; k++) {
        if (col[idx] == col[k] || abs(col[idx] - col[k]) == (idx - k)) {
            return false;
        }
    }
    return true;
}

void dfs(int idx) {
    if (idx == n) {
        cnt++;
    } else {
        for (int j = 0; j < n; j++) {
            col[idx] = j;
            if (promising(idx)) {
                dfs(idx + 1);
            }
            col[idx] = -1;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    col = vector<int>(n, -1);

    dfs(0);

    cout << cnt << '\n';
}