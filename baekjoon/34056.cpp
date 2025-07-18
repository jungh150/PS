#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<long long> a(n + 1);
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    int q;
    cin >> q;
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int c, x;
            cin >> c >> x;

            long long tmp = x;
            for (int i = c; i >= 1; i--) {
                if (tmp <= a[i]) {
                    a[i] += tmp;
                    break;
                } else {
                    tmp -= a[i];
                    a[i] += a[i];
                }
            }

            tmp = x;
            for (int i = c + 1; i < n + 1; i++) {
                if (tmp <= a[i]) {
                    a[i] += tmp;
                    break;
                } else {
                    tmp -= a[i];
                    a[i] += a[i];
                }
            }
        } else if (op == 2) {
            int c;
            cin >> c;

            cout << a[c] << '\n';
        }
    }
}