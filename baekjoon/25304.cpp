#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int x, n;
    cin >> x >> n;

    int total = 0;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        total += a * b;
    }

    if (total == x) cout << "Yes\n";
    else cout << "No\n";
}