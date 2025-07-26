#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> left(n);
    vector<int> right(n);

    left[0] = min(1, a[0]);
    for (int i = 1; i < n; i++) left[i] = min(left[i - 1] + 1, a[i]);

    right[n - 1] = min(1, a[n - 1]);
    for (int i = n - 2; i >= 0; i--) right[i] = min(right[i + 1] + 1, a[i]);

    long long ans = 0;
    for (int i = 0; i < n; i++) ans += min(left[i], right[i]);
    cout << ans << '\n';
}