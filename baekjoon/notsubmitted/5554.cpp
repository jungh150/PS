#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int sec = 0;
    for (int i = 0; i < 4; i++) {
        int x;
        cin >> x;
        sec += x;
    }

    cout << sec / 60 << '\n';
    cout << sec % 60 << '\n';
}