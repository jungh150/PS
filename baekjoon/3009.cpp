#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<int> x = vector<int>(3);
    vector<int> y = vector<int>(3);

    for (int i = 0; i < 3; i++) {
        cin >> x[i] >> y[i];
    }

    sort(x.begin(), x.end());
    sort(y.begin(), y.end());

    int ansx, ansy;

    if (x[1] == x[0]) ansx = x[2];
    else ansx = x[0];

    if (y[1] == y[0]) ansy = y[2];
    else ansy = y[0];

    cout << ansx << ' ' << ansy << '\n';
}