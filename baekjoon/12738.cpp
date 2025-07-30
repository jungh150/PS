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

    vector<int> a(n + 1);
    a[0] = -1e9 - 1;
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    vector<int> b;
    b.push_back(a[0]);

    for (int i = 1; i < n + 1; i++) {
        if (a[i] > b.back()) {
            b.push_back(a[i]);
        } else {
            int idx = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
            b[idx] = a[i];
        }
    }

    cout << b.size() - 1 << '\n';
}