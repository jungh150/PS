#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    bool isE = false;
    int cnt = 0;

    while (n--) {
        char c;
        cin >> c;
        if (c == 'E') {
            isE = true;
        } else if (c == 'W') {
            if (isE) cnt++;
            isE = false;
        }
    }

    cout << cnt << '\n';
}