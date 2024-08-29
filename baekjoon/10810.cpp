#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1, 0);

    while(m--) {
        int i, j, k;
        cin >> i >> j >> k;
        for (int x = i; x <= j; x++) a[x] = k;
    }

    for (int i = 1; i <= n; i++) cout << a[i] << ' ';
    cout << '\n';
}