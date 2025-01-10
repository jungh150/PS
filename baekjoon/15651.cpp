#include <iostream>
using namespace std;

int n, m;

void rec(int cnt, string s) {
    if (cnt == m) {
        cout << s << '\n';
    } else {
        for (int i = 1; i <= n; i++) {
            rec(cnt + 1, s + to_string(i) + ' ');
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;

    rec(0, "");
}