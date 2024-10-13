#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());

    long long maxt = 0;
    for (int i = 0; i < n; i++) {
        maxt = max(maxt, a[i] * (n - i));
    }

    cout << maxt << '\n';
}