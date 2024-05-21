#include <iostream>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    vector<bool> isPrime = vector<bool>(1000001, true);
    isPrime[1] = false;
    for (int i = 2; i < 1001; i++) {
        int tmp = 2 * i;
        while (tmp < 1000001) {
            isPrime[tmp] = false;
            tmp += i;
        }
    }

    int n;
    cin >> n;

    vector<int> a = vector<int>(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    set<int> pn;
    for (int x: a) { //!
        if (isPrime[x]) {
            pn.insert(x);
        }
    }

    long long ans = 1;
    for (int x: pn) {
        ans *= x;
    }

    if (ans == 1) {
        ans = -1;
    }

    cout << ans << '\n';
}