#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;

    int n = s.size();
    int ans = 0;

    for (int i = n / 2; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (j + i + i > n) continue;

            int sum1 = 0;
            for (int k = j; k < j + i; k++) sum1 += (s[k] - '0');
            int sum2 = 0;
            for (int k = j + i; k < j + i + i; k++) sum2 += (s[k] - '0');

            if (sum1 == sum2) {
                cout << i + i << '\n';
                return 0;
            }
        }
    }

    cout << 0 << '\n';
}