#include <iostream>
#include <vector>
using namespace std;

int mod = 16769023;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<long long> dp1(n + 1); // 0의 개수가 1개 더 많은 이진 문자열 수
    vector<long long> dp2(n + 1); // 0의 개수와 1의 개수가 같은 이진 문자열 수
    vector<long long> dp3(n + 1); // 1의 개수가 1개 더 많은 이진 문자열 수

    dp1[0] = 1;
    dp2[0] = 0;
    dp3[0] = 1;

    for (int i = 1; i < n; i++) {
        dp1[i] = dp2[i - 1];
        dp2[i] = (dp1[i - 1] + dp3[i - 1]) % mod;
        dp3[i] = dp2[i - 1];
    }

    cout << (dp1[n - 1] + dp2[n - 1] + dp3[n - 1]) % mod << '\n';
}