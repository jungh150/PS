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
    vector<vector<int>> cow(n, vector<int>(2));

    for (int i = 0; i < n; i++) {
        cin >> cow[i][0] >> cow[i][1];
    }

    sort(cow.begin(), cow.end());

    int cur = 0;
    for (int i = 0; i < n; i++) {
        if (cur < cow[i][0]) cur = cow[i][0];
        cur += cow[i][1];
    }

    cout << cur << '\n';
}