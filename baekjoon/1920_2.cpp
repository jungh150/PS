#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, m;
vector<int> a;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    a = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    cin >> m;
    while (m--) {
        int x;
        cin >> x;
        bool find = false;
        
        int start = 0;
        int end = n - 1;
        while (start <= end) {
            int mid = (start + end) / 2;
            if (a[mid] == x) {
                find = true;
                break;
            } else if (a[mid] > x) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }

        if (find) cout << 1 << '\n';
        else cout << 0 << '\n';
    }
}