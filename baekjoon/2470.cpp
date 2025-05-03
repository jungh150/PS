#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    int l = 0;
    int r = n - 1;
    int mint = 2000000001;
    int minl = -1;
    int minr = -1;

    while (l < r) {
        int tmp = a[l] + a[r];
        if (abs(tmp) < mint) {
            mint = abs(tmp);
            minl = l;
            minr = r;
        }
        if (tmp > 0) r--;
        else l++;
    }

    cout << a[minl] << ' ' << a[minr] << '\n';
}