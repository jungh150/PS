#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, l;
    cin >> n >> l;

    for (int k = l; k <= 100; k++) {
        if ((2 * n) % k != 0) continue;
        int tmp = (2 * n / k) - k + 1;
        if (tmp >= 0 && tmp % 2 == 0) {
            int a = tmp / 2;
            for (int i = 0; i < k; i++) cout << a + i << ' ';
            cout << '\n';
            return 0;
        }
    }

    cout << "-1\n";
}