#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int d, p, q;
    cin >> d >> p >> q;

    if (p > q) {
        int tmp = p;
        p = q;
        q = tmp;
    }

    // p <= q

    int maxrem = 0;
    int maxa = 0;
    int tq = 0;

    int dif, rem, quo;
    while (1) {
        dif = d - tq;
        if (dif + p <= 0) break;
        rem = dif % p;

        if (rem == 0) {
            quo = dif / p;
            maxa = tq + p * quo;
            cout << maxa << '\n';
            return 0;
        } else if (rem < 0) {
            quo = dif / p;
            rem += p;
        } else {
            quo = dif / p + 1;
        }

        if (rem > maxrem) {
            maxrem = rem;
            maxa = tq + p * quo;
        } else if (rem == maxrem) {
            break;
        }

        tq += q;
    }
    
    cout << maxa << '\n';
}