#include <iostream>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int cnt = 0;

    while (n--) {
        int x;
        cin >> x;

        if (x < 2) continue;

        bool isPrime = true;
        int tmp = sqrt(x);
        for (int i = 2; i <= tmp; i++) {
            if (x % i == 0) {
                isPrime = false;
                break;
            }
        }

        if (isPrime) cnt++;
    }

    cout << cnt << '\n';
}