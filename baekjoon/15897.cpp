#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    long long ans = 0;
    long long i = 1;
    while (i < n) {
        long long cnt = ((n - 1) % i) / ((n - 1) / i) + 1;
        ans += ((n - 1) / i) * cnt;
        i += cnt;
    }
    ans += n;
    
    cout << ans << '\n';
}