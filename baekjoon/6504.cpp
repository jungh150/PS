#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<int> fib(25);

    fib[0] = 0;
    fib[1] = 1;
    fib[2] = 2;
    for (int i = 3; i < 25; i++) fib[i] = fib[i - 1] + fib[i - 2];

    int t;
    cin >> t;

    while (t--) {
        vector<bool> b(25, 0);
        
        int x;
        cin >> x;
        
        for (int i = 24; i >= 1; i--) {
            if (x >= fib[i]) {
                x -= fib[i];
                b[i] = 1;
                i--;
            }
        }

        for (int i = 1; i < 24; i++) {
            b[i] = b[i + 1];
        }
        b[24] = 0;

        int ans = 0;
        for (int i = 1; i < 25; i++) {
            if (b[i]) ans += fib[i];
        }

        cout << ans << '\n';
    }
}