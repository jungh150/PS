#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long n, a, pa, b, pb;
    cin >> n >> a >> pa >> b >> pb;

    long long ansa = 0;
    long long ansb = 0;

    long long ans = 0;
    long long an = n / pa;
    for (int ta = 0; ta <= an; ta++) {
        long long tb = (n - pa * ta) / pb;
        long long tmp = a * ta + b * tb;
        if (tmp > ans) {
            ans = tmp;
            ansa = ta;
            ansb = tb;
        }
    }

    cout << ansa << ' ' << ansb << '\n';
}