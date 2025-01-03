#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;
    
    while (t--) {
        int f, r, n;
        cin >> f >> r >> n;

        int ans = 2 * f + (r + 1);
        vector<vector<int>> o(f + 1, vector<int>());

        for (int i = 0; i < n; i++) {
            int a, b;
            cin >> a >> b;
            o[a].push_back(b);
        }

        for (int i = 1; i <= f; i++) {
            o[i].push_back(0);
            o[i].push_back(r + 1);
            sort(o[i].begin(), o[i].end());

            int tmp = 1000;
            int os = o[i].size();
            for (int j = 1; j < os; j++) {
                tmp = min(tmp, 2 * (o[i][j - 1] + r + 1 - o[i][j]));
            }
            ans += tmp;
        }

        cout << ans << '\n';
    }
}