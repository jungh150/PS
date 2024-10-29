#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int mg = 0;
    int ms = 0;

    for (int i = 0; i < 4; i++) {
        int x;
        cin >> x;
        mg += x;
    }

    for (int i = 0; i < 4; i++) {
        int x;
        cin >> x;
        ms += x;
    }

    if (mg >= ms) cout << mg << '\n';
    else cout << ms << '\n';
}