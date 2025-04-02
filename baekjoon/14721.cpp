#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> x(n);
    vector<int> y(n);

    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];

    int mina = 101;
    int minb = 101;
    long long mins = -1;

    for (int a = 1; a < 101; a++) {
        for (int b = 1; b < 101; b++) {
            long long sumt = 0;
            for (int i = 0; i < n; i++) {
                long long tmp = y[i] - (a * x[i] + b);
                sumt += tmp * tmp;
            }
            if (mins == -1 || sumt < mins) {
                mins = sumt;
                mina = a;
                minb = b;
            }
        }
    }

    cout << mina << ' ' << minb << '\n';
}