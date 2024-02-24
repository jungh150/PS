#include <bits/stdc++.h>
using namespace std;

const int mx = 1e5;
const int mod = 1e9 + 7;

int main() {
    cin.tie(0); ios_base::sync_with_stdio(0);
    int n; cin >> n;
    vector<int> arr(n);
    fill(arr.begin(), arr.end(), 0);
    auto it = arr.begin();
    for (int i = 0; i < n; i++) cin >> arr[i];
    for (int &a: arr) cin >> a;

    int a[mx + 1];
    fill(a, a + n + 1, 0);
    iota(a, a + n + 1, 0);
}