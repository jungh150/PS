#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int q;
    cin >> q;

    while (q--) {
        string s;
        cin >> s;

        int cnt = 0;
        int sn = s.size();
        for (int i = 0; i < sn; i++) {
            if (s.substr(i, 3) == "WOW") cnt++;
        }

        cout << cnt << '\n';
    }
}