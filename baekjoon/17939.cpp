#include <iostream>
#include <vector>
using namespace std;

int n;
vector<int> c;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    c = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> c[i];

    int ans = 0;
    int s = 0;
    int e = c.size();
    while (s < e) {
        int maxv = 0;
        int maxi = -1;
        for (int i = s; i < e; i++) {
            if (c[i] >= maxv) {
                maxv = c[i];
                maxi = i;
            }
        }
        for (int i = s; i < maxi; i++) {
            ans -= c[i];
        }
        ans += maxv * (maxi - s);
        s = maxi + 1;
    }

    cout << ans << '\n';
}