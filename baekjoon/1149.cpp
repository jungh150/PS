#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> rgb = vector<vector<int>>(n + 1, vector<int>(3));
    rgb[0][0] = rgb[0][1] = rgb[0][2] = 0;
    for (int i = 1; i < n + 1; i++) {
        cin >> rgb[i][0] >> rgb[i][1] >> rgb[i][2];
    }

    vector<vector<int>> dp = vector<vector<int>>(n + 1, vector<int>(3));
    dp[0][0] = dp[0][1] = dp[0][2] = 0;
    for (int i = 0; i < 3; i++) {
        dp[1][i] = rgb[1][i];
    }

    for (int i = 2; i < n + 1; i++) {
        
    }
}