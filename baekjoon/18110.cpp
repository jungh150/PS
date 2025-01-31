#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    if (n == 0) {
        cout << 0 << '\n';
        return 0;
    }

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    int ex = floor(n * 0.15 + 0.5);
    int sum = 0;

    for (int i = ex; i < n - ex; i++) {
        sum += a[i];
    }

    double avg = double(sum) / (n - 2 * ex);

    cout << floor(avg + 0.5) << '\n';

    return 0;
}
