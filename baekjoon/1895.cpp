#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int r, c;
    cin >> r >> c;

    vector<vector<int>> a(r, vector<int>(c));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> a[i][j];
        }
    }

    int t;
    cin >> t;

    int ans = 0;

    for (int i = 0; i < r - 2; i++) {
        for (int j = 0; j < c - 2; j++) {
            vector<int> tmp;
            for (int k = i; k < i + 3; k++) {
                for (int l = j; l < j + 3; l++) {
                    tmp.push_back(a[k][l]);
                }
            }
            sort(tmp.begin(), tmp.end());
            if (tmp[4] >= t) ans++;
        }
    }

    cout << ans << '\n';
}