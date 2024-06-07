#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    for (int tmpt = 1; tmpt <= t; tmpt++) {
        int n;
        cin >> n;

        vector<int> a = vector<int>(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        while (n > 2) {
            for (int i = 0; i < (n + 1) / 2; i++) {
                a[i] += a[n - 1 - i];
            }
            n = ceil((n + 1) / 2);
        }

        cout << "Case #" << tmpt << ": ";
        if (a[0] > a[1]) {
            cout << "Alice\n";
        } else {
            cout << "Bob\n";
        }
    }
}