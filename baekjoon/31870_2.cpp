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
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    // ascending order
    vector<int> at = a;
    int asccnt = 0;
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (at[j] > at[j + 1]) {
                int tmp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = tmp;
                asccnt++;
            }
        }
    }

    // descending order
    at = a;
    int descnt = 0;
    for (int i = n - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (at[j] < at[j + 1]) {
                int tmp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = tmp;
                descnt++;
            }
        }
    }

    cout << min(asccnt, descnt + 1) << '\n';
}