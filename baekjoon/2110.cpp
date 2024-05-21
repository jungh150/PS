#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n, c;
    cin >> n >> c;

    vector<int> home = vector<int>(n);
    for (int i = 0; i < n; i++) {
        cin >> home[i];
    }

    sort(home.begin(), home.end());

    int l = 1;
    int r = home[n - 1] - home[0] + 1;
    int m;

    while (l < r) {
        m = (l + r) / 2;
        int cnt = 1;
        int pre = home[0];
        for (int x: home) {
            if ((x - pre) >= m) {
                cnt++;
                pre = x;
            }
        }
        if (cnt >= c) {
            l = m + 1;
        }
        else {
            r = m;
        }
    }

    cout << (l - 1) << '\n';
}