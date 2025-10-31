#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int num = 4000001;
    vector<bool> p(num, 1);
    p[0] = p[1] = 0;

    int sqnum = sqrt(num);
    for (int i = 2; i <= sqnum; i++) {
        if (p[i]) {
            for (int j = i * i; j < num; j += i) {
                p[j] = 0;
            }
        }
    }

    vector<int> prime; // 소수 배열
    prime.push_back(0);
    for (int i = 1; i < num; i++) {
        if (p[i]) prime.push_back(i);
    }

    int pn = prime.size();
    vector<int> dp(pn, 0); // 부분합 배열
    for (int i = 1; i < pn; i++) {
        dp[i] = dp[i - 1] + prime[i];
    }

    int n;
    cin >> n;

    int cnt = 0;
    int l = 0;
    int r = 0;
    while (l <= r && r < pn) {
        if (dp[r] - dp[l] == n) {
            cnt++;
            r++;
        } else if (dp[r] - dp[l] > n) {
            l++;
        } else {
            r++;
        }
    }

    cout << cnt << '\n';
}