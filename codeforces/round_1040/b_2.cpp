#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n, s;
        cin >> n >> s;

        vector<int> a(3, 0);
        int sumt = 0;

        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            a[x]++;
            sumt += x;
        }

        if (sumt > s) {
            for (int i = 0; i < a[0]; i++) cout << 0 << ' ';
            for (int i = 0; i < a[1]; i++) cout << 1 << ' ';
            for (int i = 0; i < a[2]; i++) cout << 2 << ' ';
            cout << '\n';
        } else if (sumt == s) {
            cout << -1 << '\n';
        } else if (sumt + 1 == s) {
            for (int i = 0; i < a[0]; i++) cout << 0 << ' ';
            for (int i = 0; i < a[2]; i++) cout << 2 << ' ';
            for (int i = 0; i < a[1]; i++) cout << 1 << ' ';
            cout << '\n';
        } else {
            cout << -1 << '\n';
        }
    }
}