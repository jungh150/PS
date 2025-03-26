#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    while (n--) {
        long long ans = 0;

        int m;
        cin >> m;

        vector<vector<int>> mission(m, vector<int>(3));
        for (int i = 0; i < m; i++) {
            int k, d, a;
            cin >> k >> d >> a;
            mission[i][0] = k;
            mission[i][1] = -1 * d;
            mission[i][2] = a;
        }

        vector<int> kda(3);
        for (int i = 0; i < 3; i++) cin >> kda[i];

        for (int i = 0; i < m; i++) {
            long long tmp = 0;
            for (int j = 0; j < 3; j++) {
                tmp += (long long) mission[i][j] * kda[j];
            }
            if (tmp > 0) ans += tmp;
        }

        cout << ans << '\n';
    }
}