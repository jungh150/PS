#include <iostream>
using namespace std;

int cnt[10001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    int idx = 1;
    while (idx < 10001) {
        while (cnt[idx]--) cout << idx << '\n';
        idx++;
    }
}