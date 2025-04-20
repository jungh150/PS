#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    int tmp = 1;
    int cnt = 0;
    while (tmp <= n) {
        if (n % tmp == 0) {
            cnt++;
            if (cnt == k) {
                cout << tmp << '\n';
                return 0;
            }
        }
        tmp++;
    }

    cout << 0 << '\n';
}