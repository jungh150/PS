#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool compare(vector<int> x, vector<int> y) {
    if (x[1] != y[1]) return x[1] > y[1];
    if (x[2] != y[2]) return x[2] > y[2];
    if (x[3] != y[3]) return x[3] > y[3];
    return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> a(n, vector<int>(4));
    for (int i = 0; i < n; i++) cin >> a[i][0] >> a[i][1] >> a[i][2] >> a[i][3];

    sort(a.begin(), a.end(), compare);

    int idx = 1;
    int tmp = 1;

    if (a[0][0] == k) {
        cout << idx << '\n';
        return 0;
    }

    for (int i = 1; i < n; i++) {
        if (a[i][1] == a[i - 1][1] && a[i][2] == a[i - 1][2] && a[i][3] == a[i - 1][3]) {
            tmp++;
        } else {
            idx += tmp;
            tmp = 1;
        }

        if (a[i][0] == k) {
            cout << idx << '\n';
            break;
        }
    }
}