#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> k;

    int unit = n / k;
    for (int i = 0; i < k; i++) {
        sort(a.begin() + i * unit, a.begin() + (i + 1) * unit);
    }

    for (int i = 0; i < n; i++) cout << a[i] << ' ';
    cout << '\n';
}