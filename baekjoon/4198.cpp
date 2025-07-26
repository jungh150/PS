#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // dp[i][j]: i번째 열차를 앞(j=0), 뒤(j=1), 혹은 사용하지 않았을 때(j=2) 최대 {앞 중량, 뒤 중량, 열차 배열 길이}
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(3));
    dp[0][0] = {a[0], a[0], 1};
    dp[0][1] = {a[0], a[0], 1};
    dp[0][2] = {a[0], a[0], 0};
}