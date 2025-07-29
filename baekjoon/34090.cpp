#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    long long n;
    cin >> n;

    map<int, int> m;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        if (m.count(x)) m[x]++;
        else m.insert({x, 1});
    }

    long long ans = n * (n + 1) / 2;
    for (auto it = m.begin(); it != m.end(); it++) {
        long long cnt = it->second;
        ans -= (cnt * (cnt + 1) / 2);
    }
    ans++;

    cout << ans << '\n';
}