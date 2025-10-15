#include <iostream>
using namespace std;

void solve() {
    int br, bc, dr, dc, jr, jc;
    cin >> br >> bc >> dr >> dc >> jr >> jc;

    int b = max(abs(jr - br), abs(jc - bc));
    int d = abs(jr - dr) + abs(jc - dc);

    if (b < d) cout << "bessie\n";
    else if (b == d) cout << "tie\n";
    else cout << "daisy\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}