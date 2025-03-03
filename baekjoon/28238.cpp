#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<vector<bool>> a(n, vector<bool>(5));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            int x;
            cin >> x;
            a[i][j] = x;
        }
    }

    int ans = 0;
    pair<int, int> ansp = {0, 1};
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            int tmp = 0;

            for (int k = 0; k < n; k++) {
                if (a[k][i] && a[k][j]) tmp++;
            }

            if (tmp > ans) {
                ans = tmp;
                ansp.first = i;
                ansp.second = j;
            }
        }
    }

    cout << ans << '\n';
    for (int i = 0; i < 5; i++) {
        if (i == ansp.first || i == ansp.second) cout << 1 << ' ';
        else cout << 0 << ' ';
    }
    cout << '\n';
}