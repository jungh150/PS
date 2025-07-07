#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    vector<long long> dif(n + 2, 0);

    int m;
    cin >> m;

    while (m--) {
        int q;
        cin >> q;
        if (q == 1) {
            int i, j, k;
            cin >> i >> j >> k;
            dif[i] += k;
            dif[j + 1] -= k;
        } else if (q == 2) {
            int x;
            cin >> x;
            long long res = a[x];
            for (int i = 1; i < x + 1; i++) res += dif[i];
            cout << res << '\n';
        }
    }
}