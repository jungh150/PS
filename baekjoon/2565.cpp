#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> line = vector<vector<int>>(n + 1, vector<int>(2));
    line[0][0] = line[0][1] = 0;
    for (int i = 0; i < n; i++) {
        cin >> line[i][0] >> line[i][1];
    }

    sort(line.begin(), line.end());
    int maxa = 0;

    vector<int> dp = vector<int>(n + 1, 0);

    dp[0] = 0;
    for (int i = 1; i < n + 1; i++) {
        int maxt = 0;
        for (int j = 0; j < i; j++) {
            if (line[i][1] >= line[j][1]) {
                maxt = max(maxt, dp[j] + 1);
            }
        }
        dp[i] = maxt;
        maxa = max(maxa, dp[i]);
    }

    cout << (n - maxa) << '\n';
}