#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    int x;
    long long sum = 0;
    long long ans = 0;

    for (int i = 0; i < n; i++) {
        cin >> x;
        ans += sum * x;
        sum += x;
    }

    cout << ans << '\n';
    
}