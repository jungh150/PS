#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, d;
    cin >> n >> d;

    vector<int> cnt(10, 0);

    for (int i = 1; i <= n; i++) {
        int tmp = i;
        while (tmp > 0) {
            cnt[tmp % 10]++;
            tmp /= 10;
        }
    }

    cout << cnt[d] << '\n';
}