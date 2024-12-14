#include <iostream>
#include <set>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    while (cin >> n >> m) {
        int ans = 0;
        for (int i = n; i <= m; i++) {
            int tmp = i;
            bool psb = true;
            set<int> s;
            while (tmp > 0) {
                int rem = tmp % 10;
                if (s.find(rem) != s.end()) {
                    psb = false;
                    break;
                } else {
                    s.insert(rem);
                }
                tmp /= 10;
            }
            if (psb) ans++;
        }
        cout << ans << '\n';
    }
}