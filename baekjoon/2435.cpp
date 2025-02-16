#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int sum = 0;
    int s = 0;
    int e = k - 1;

    for (int i = s; i <= e; i++) sum += a[i];
    int maxs = sum;

    while (e < n - 1) {
        sum -= a[s];
        s++;
        e++;
        sum += a[e];
        maxs = max(maxs, sum);
    }

    cout << maxs << '\n';
}