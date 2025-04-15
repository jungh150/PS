#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int p;
    cin >> p;

    while (p--) {
        int ans = 0;

        int tn;
        cin >> tn;

        vector<int> a(12);
        for (int i = 0; i < 12; i++) cin >> a[i];

        for (int i = 1; i < 11; i++) {
            for (int j = i; j < 11; j++) {
                bool flag = true;
                for (int k = i; k <= j; k++) {
                    if (a[k] <= a[i - 1] || a[k] <= a[j + 1]) {
                        flag = false;
                        break;
                    }
                }
                if (flag) ans++;
            }
        }

        cout << tn << ' ' << ans << '\n';
    }
}