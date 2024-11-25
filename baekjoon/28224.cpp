#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];

    long long ans = 0;
    int pre = 0;
    for (int i = n - 1; i >= 0; i--) {
        pre = min(pre + 1, v[i]);
        ans += pre;
    }

    cout << ans << '\n';
}