#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    
    while (cin >> n) {
        bool notJolly = false;
        vector<int> a(n);
        vector<bool> chk(n, false);

        for (int i = 0; i < n; i++) cin >> a[i];

        for (int i = 1; i < n; i++) {
            int diff = abs(a[i] - a[i - 1]);

            if (diff < 1 || diff > n - 1 || chk[diff]) {
                cout << "Not jolly\n";
                notJolly = true;
                break;
            } else {
                chk[diff] = true;
            }
        }

        if (notJolly) continue;

        for (int i = 1; i < n; i++) {
            if (!chk[i]) {
                cout << "Not jolly\n";
                notJolly = true;
                break;
            }
        }

        if (!notJolly) cout << "Jolly\n";
    }
}