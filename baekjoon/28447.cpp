#include <iostream>
#include <vector>
using namespace std;

int n, k;
vector<vector<int>> c;
vector<int> ing;
int ans = -1e9;

void bt(int cnt, int pre) {
    if (cnt == k) {
        int res = 0;
        for (int i = 0; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                res += c[ing[i]][ing[j]];
            }
        }
        ans = max(ans, res);
        return;
    }
    for (int i = pre + 1; i < n; i++) {
        ing.push_back(i);
        bt(cnt + 1, i);
        ing.pop_back();
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;

    c = vector<vector<int>>(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> c[i][j];
        }
    }

    bt(0, -1);

    cout << ans << '\n';
}