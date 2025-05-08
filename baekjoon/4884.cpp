#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<long long> pow2(40);
    long long tmp = 1;
    for (int i = 0; i < 40; i++) {
        pow2[i] = tmp;
        tmp *= 2;
    }

    while (1) {
        long long g, t, a, d, x, y;
        cin >> g >> t >> a >> d;

        if (g == -1) return 0;

        long long tn = g * a + d;
        long long tntotal;
        for (int i = 0; i < 40; i++) {
            if (pow2[i] >= tn) {
                tntotal = pow2[i];
                break;
            }
        }

        x = g * t * (t - 1) / 2 + tntotal - 1;
        y = tntotal - tn;

        cout << g << "*" << a << "/" << t << "+" << d << "=" << x << "+" << y << '\n';
    }
}