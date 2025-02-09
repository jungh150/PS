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

    vector<int> a(n);
    vector<int> b(m);

    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];

    // 이분 탐색을 위해 배열 b 정렬
    sort(b.begin(), b.end());

    long long hi = 0, arc = 0, draw = 0;

    for (int i = 0; i < n; i++) {
        auto lower = lower_bound(b.begin(), b.end(), a[i]);
        auto upper = upper_bound(b.begin(), b.end(), a[i]);

        hi += lower - b.begin();
        arc += b.end() - upper;
        draw += upper - lower;
    }

    cout << hi << ' ' << arc << ' ' << draw << '\n';
}