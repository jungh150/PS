#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a, b, c, d;
    cin >> a >> b >> c >> d;

    int n;
    cin >> n;

    int ans = 0;
    while (n--) {
        int u, v;
        cin >> u >> v;
        
        int tmp = a * (v - b) * (v - b) + c;
        if (tmp == u && c >= u) ans++;
    }

    cout << ans << '\n';
}