#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    vector<int> a = vector<int>(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> b = vector<int>(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int aidx = 0;
    int bidx = 0;
    int cnt = 0;
    bool ans = false;

    while (aidx < n && bidx < m) {
        if (a[aidx] < b[bidx]) {
            aidx++;
            cnt++;
        }
        else {
            bidx++;
            cnt = 0;
        }
        if (cnt == 2) {
            ans = true;
            break;
        }
    }

    if (aidx < n - 1) {
        ans = true;
    }

    if (ans) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}