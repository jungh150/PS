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

    vector<vector<int>> arr(n, vector<int>(4));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> arr[i][j];
        }
    }

    vector<int> ab;
    vector<int> cd;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ab.push_back(arr[i][0] + arr[j][1]);
            cd.push_back(-(arr[i][2] + arr[j][3]));
        }
    }

    sort(cd.begin(), cd.end());
    long long ans = 0;

    for (int x: ab) {
        ans += upper_bound(cd.begin(), cd.end(), x) - lower_bound(cd.begin(), cd.end(), x);
    }

    cout << ans << '\n';
}