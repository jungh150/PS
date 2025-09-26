#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void solve() {
    long long n;
    cin >> n;

    vector<long long> cnt(15);
    long long s = 1;
    long long e = 10;
    for (int i = 0; i < 7; i++) {
        cnt[2 * i + 1] = cnt[2 * i + 2] = e - s; // s부터 e-1까지의 개수
        s *= 10;
        e *= 10;
    }

    int k = to_string(n).size(); // 자리수
    
    long long ans = 0;
    for (int i = 1; i < k; i++) ans += cnt[i];

    int x = (k + 1) / 2;
    s = (long long) pow(10, x - 1);
    e = n / (long long) pow(10, k - x);
    ans += (e - s); // s부터 e-1까지의 개수

    string str = to_string(e);
    string tmp = str;
    reverse(tmp.begin(), tmp.end());
    if (k % 2 == 0) {
        str += tmp;
    } else {
        str.pop_back();
        str += tmp;
    }
    if (n >= stoll(str)) ans++;

    cout << ans << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}