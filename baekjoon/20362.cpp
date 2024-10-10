#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    string ansp;
    cin >> n >> ansp;

    vector<string> p(n);
    vector<string> c(n);

    for (int i = 0; i < n; i++) cin >> p[i] >> c[i];

    string ans = "";
    int cnt = 0;
    for (int i = n - 1; i >= 0; i--)  {
        if (p[i] == ansp) ans = c[i];
        else if (c[i] == ans) cnt++;
    }

    cout << cnt << '\n';
}