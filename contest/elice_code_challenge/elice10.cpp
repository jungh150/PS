#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n;
vector<int> a;

bool psb(int k) {//3
    //cout << k << '\n';
    for (int i = 0; i <= n - k; i++) {//0, 1, 2
        vector<int> b;
        for (int j = i; j < i + k; j++) {
            b.push_back(a[j]);
        }
        sort(b.begin(), b.end());
        bool ispossible = true;
        //for (int x: b) cout << x << ' ';
        //cout << '\n';
        for (int i = 0; i < k; i++) {
            if (b[i] < i + 1) {
                ispossible = false;
                break;
            }
        }
        if (ispossible) return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n; //5
    a = vector<int>(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int l = 1;
    int r = n + 1;
    while (l < r) {
        int m = (l + r) / 2;//3
        if (psb(m)) l = m + 1;
        else r = m;
    }

    cout << l - 1 << '\n';
}
