#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) a[i] = i;

    while (m--) {
        int i, j, k;
        cin >> i >> j >> k;

        vector<int> tmp;
        for (int x = i; x < k; x++) tmp.push_back(a[x]);

        int idx = i;
        for (int x = k; x <= j; x++) a[idx++] = a[x];

        for (int x: tmp) a[idx++] = x;
    }

    for (int i = 1; i <= n; i++) cout << a[i] << ' ';
    cout << '\n';
}