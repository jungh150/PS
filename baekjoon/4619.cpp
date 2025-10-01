#include <iostream>
#include <cmath>
using namespace std;

void solve() {
    while (1) {
        long long b, n;
        cin >> b >> n;

        if (b == 0 && n == 0) break;

        if (n == 1) {
            cout << b << '\n';
        } else {
            long long minv = 1e15;
            long long mini = 0;
            for (long long i = 0; i <= b; i++) {
                long long tmp = b - pow(i, n);
                bool fin = false;

                if (tmp < 0) {
                    tmp = -tmp;
                    fin = true;
                }

                if (tmp < minv) {
                    minv = tmp;
                    mini = i;
                }

                if (fin) break;
            }
            cout << mini << '\n';
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}