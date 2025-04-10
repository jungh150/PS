#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int ans = 0;

    // i <= j <= k 를 만족하도록 찾기
    for (int i = 1; i < n - 1; i++) {
        for (int j = i; j < n - 1; j++) {
            int k = n - i - j;
            if (k < j) break;
            if (i + j > k) ans++;
        }
    }

    cout << ans << '\n';
}