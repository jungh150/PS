#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int l = 0;
    int r = n - 1;
    int dif = 2000000000;
    int la = 0;
    int ra = 0;

    while (l < r) {
        if (abs(a[r] + a[l]) < dif) {
            dif = abs(a[r] + a[l]);
            la = l;
            ra = r;
        }
        if (a[r] + a[l] > 0) r--;
        else l++;
    }

    cout << a[la] << ' ' << a[ra] << '\n';
}