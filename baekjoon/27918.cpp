#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int x = 0;
    int y = 0;

    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == 'D') x++;
        else if (c == 'P') y++;

        if (abs(x - y) >= 2) {
            cout << x << ":" << y << '\n';
            return 0;
        }
    }

    cout << x << ":" << y << '\n';
}