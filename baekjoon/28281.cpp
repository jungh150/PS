#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, x;
    cin >> n >> x;

    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    int mina = 2e9 + 1;
    for (int i = 0; i < n - 1; i++) {
        mina = min(mina, a[i] + a[i + 1]);
    }

    cout << mina * x << '\n';
}