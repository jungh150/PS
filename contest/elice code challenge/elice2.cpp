#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    while (m--) {
        int i, j, k;
        cin >> i >> j >> k;

        vector<int> b;
        for (int x = i - 1; x < j; x++) {
            b.push_back(a[x]);
        }
        sort(b.begin(), b.end());

        cout << b[k - 1] << '\n';
    }
}