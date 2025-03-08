#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> dp1(n);
    vector<int> dp2(n);

    for (int i = 0; i < n; i++) {
        int maxt = 0;
        for (int j = 0; j < i; j++) {
            if (a[i] > a[j]) maxt = max(maxt, dp1[j]);
        }
        dp1[i] = maxt + 1;
    }

    for (int i = n - 1; i >= 0; i--) {
        int maxt = 0;
        for (int j = n - 1; j > i; j--) {
            if (a[i] > a[j]) maxt = max(maxt, dp2[j]);
        }
        dp2[i] = maxt + 1;
    }

    int maxa = 0;
    for (int i = 0; i < n; i++) {
        int tmpa = dp1[i] + dp2[i] - 1;
        maxa = max(maxa, tmpa);
    }

    cout << maxa << '\n';
}