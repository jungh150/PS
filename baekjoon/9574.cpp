#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, x, y, z;
    cin >> n >> x >> y >> z;

    vector<vector<int>> c(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
        cin >> c[i][0] >> c[i][1];
    }

    sort(c.begin(), c.end());

    long long maxt = 0;

    for (int i = 0; i < n; i++) {
        long long tmp = 0;
        // temperature = c[i][0]
        for (int j = 0; j < i; j++) {
            if (c[i][0] <= c[j][1]) {
                tmp += y;
            } else {
                tmp += z;
            }
        }
        tmp += (y + (n - 1 - i) * x);
        if (tmp > maxt) {
            maxt = tmp;
        }
    }

    cout << maxt << '\n';
}