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

    int cnt = 0;
    int tmp = (n + 1) / 2;

    for (int i = 0; i < tmp; i++) cnt += log2(a[i]);

    cout << cnt + 1 << '\n';
}