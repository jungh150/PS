#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
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

    long long mint = 3000000001;
    int mini = -1;
    int minl = -1;
    int minr = -1;

    for (int i = 0; i <= n - 3; i++) {
        int l = i + 1;
        int r = n - 1;
        while (l < r) {
            long long tmp = (long long) a[i] + a[l] + a[r];
            if (abs(tmp) < mint) {
                mint = abs(tmp);
                mini = i;
                minl = l;
                minr = r;
            }
            if (tmp > 0) r--;
            else l++;
        }
    }

    cout << a[mini] << ' ' << a[minl] << ' ' << a[minr] << '\n';
}