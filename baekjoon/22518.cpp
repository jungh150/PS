#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<int>> a(n + 1, vector<int>(2));
    vector<int> dp1(n + 1, 0);
    vector<int> dp2(n + 1, 0);

    a[0][0] = 0;
    a[0][1] = 0;
    for (int i = 1; i < n + 1; i++) cin >> a[i][0] >> a[i][1];

    dp1[1] = a[1][1];
    dp2[1] = a[1][0];

    for (int i = 2; i < n + 1; i++) {
        dp1[i] = max(dp1[i - 1] + abs(a[i][0] - a[i - 1][0]) + a[i][1], dp2[i - 1] + abs(a[i][0] - a[i - 1][1]) + a[i][1]);
        dp2[i] = max(dp1[i - 1] + abs(a[i][1] - a[i - 1][0]) + a[i][0], dp2[i - 1] + abs(a[i][1] - a[i - 1][1]) + a[i][0]);
    }

    cout << max(dp1[n], dp2[n]) << '\n';
}