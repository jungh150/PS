#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int k, n;
    cin >> k >> n;

    vector<long long> data(k);
    for (int i = 0; i < k; i++) {
        cin >> data[i];
    }

    long long l = 0;
    long long r = data[0] + 1;

    while (l < r) {
        long long m = (l + r) / 2;
        int cnt = 0;
        for (int i = 0; i < k; i++) {
            cnt += data[i] / m;
        }
        if (cnt >= n)
            l = m + 1;
        else if (cnt < n)
            r = m;
    }

    cout << l - 1 << '\n';

    return 0;
}