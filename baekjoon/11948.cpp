#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a[4];
    int b[2];

    for (int i = 0; i < 4; i++) cin >> a[i];
    for (int i = 0; i < 2; i++) cin >> b[i];

    sort(a, a + 4);
    sort(b, b + 2);

    int ans = a[1] + a[2] + a[3] + b[1];
    cout << ans << '\n';
}