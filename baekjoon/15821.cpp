#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    vector<double> a(n);

    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        double maxt = 0;
        for (int j = 0; j < p; j++) {
            double x, y;
            cin >> x >> y;
            double dst = x * x + y * y;
            maxt = max(maxt, dst);
        }
        a[i] = maxt;
    }

    sort(a.begin(), a.end());

    cout << fixed;
    cout.precision(2);
    cout << a[k - 1] << '\n';
}