#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n;
    string s;
    cin >> n >> s;

    int a = 0;
    int b = 0;
    int c = 0;

    for (int i = 0; i < n; i++) {
        if (i % 3 == 0 && s[i] == 'A') a++;
        else if (i % 3 == 1 && s[i] == 'B') a++;
        else if (i % 3 == 2 && s[i] == 'C') a++;

        if (i % 4 == 0 && s[i] == 'B') b++;
        else if (i % 4 == 1 && s[i] == 'A') b++;
        else if (i % 4 == 2 && s[i] == 'B') b++;
        else if (i % 4 == 3 && s[i] == 'C') b++;

        if ((i % 6 == 0 || i % 6 == 1) && s[i] == 'C') c++;
        else if ((i % 6 == 2 || i % 6 == 3) && s[i] == 'A') c++;
        else if ((i % 6 == 4 || i % 6 == 5) && s[i] == 'B') c++;
    }

    int ans = max(max(a, b), c);
    cout << ans << '\n';
    if (a == ans) cout << "Adrian\n";
    if (b == ans) cout << "Bruno\n";
    if (c == ans) cout << "Goran\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}