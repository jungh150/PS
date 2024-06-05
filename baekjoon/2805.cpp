#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    int maxt = 0;

    vector<int> t = vector<int>(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
        maxt = max(maxt, t[i]);
    }

    int l = 0;
    int r = maxt + 1;
    int mid;

    while (l < r) {
        long long take = 0;
        mid = (l + r) / 2;
        for (int i = 0; i < n; i++) {
            int tmp = t[i] - mid;
            if (tmp > 0) {
                take += tmp;
            }
        }
        if (take >= m) {
            l = mid + 1;
        } else {
            r = mid;
        }
    }

    cout << l - 1 << '\n';
}