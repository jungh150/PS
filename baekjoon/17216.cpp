#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a = vector<int>(n + 1);
    a[0] = 0;
    for (int i = 1; i < n + 1; i++) {
        cin >> a[i];
    }

    vector<int> dp = vector<int>(n + 1);
    dp[0] = 0;
    int maxa = 0;

    for (int i = 0; i < n + 1; i++) {
        int maxt = 0;
        for (int j = 0; j < i; j++) {
            if (a[j] > a[i]) {
                maxt = max(maxt, dp[j]);
            }
        }
        dp[i] = maxt + a[i];
        maxa = max(maxa, dp[i]);
    }

    cout << maxa << '\n';
}