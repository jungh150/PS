#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, s;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> s;

    sort(a.begin(), a.end());

    int cnt = 0;
    int i = 0;
    int j = n - 1;
    while (i < j) {
        if (a[i] + a[j] == s) {
            cnt++;
            i++;
            j--;
        } else if (a[i] + a[j] < s) {
            i++;
        } else {
            j--;
        }
    }

    cout << cnt << '\n';
}