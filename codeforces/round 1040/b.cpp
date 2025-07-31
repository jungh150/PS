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
        } else {
            int dif = s - sumt;
            cout << dif << '\n';
            bool psb = false;
            for (int i = 0; i < 1000; i++) {
                int tmp = dif - 2 * i;
                if (tmp < 0) continue;
                if (tmp % 3 == 0) {
                    // can make
                    psb = true;
                    break;
                }
            }
            if (psb) {
                cout << -1 << '\n';
            } else {
                cout << "0 2 1 ";
                for (int i = 0; i < a[0] - 1; i++) cout << 0 << ' ';
                for (int i = 0; i < a[1] - 1; i++) cout << 1 << ' ';
                for (int i = 0; i < a[2] - 1; i++) cout << 2 << ' ';
                cout << '\n';
            }
        }
    }
}