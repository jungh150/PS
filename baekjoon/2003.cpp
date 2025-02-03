#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    long long m;
    cin >> n >> m;

    vector<int> a(n + 1, 0);
    for (int i = 1; i < n + 1; i++) cin >> a[i];

    int s = 0;
    int e = 0;
    long long res = 0;
    int cnt = 0;
    while (s < n + 1 && e < n + 1) {
        if (res < m) {
            e++;
            res += a[e];
        } else if (res > m) {
            res -= a[s];
            s++;
        } else {
            cnt++;
            e++;
            res += a[e];
        }
    }

    cout << cnt << '\n';
}