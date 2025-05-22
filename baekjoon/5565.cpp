#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int sumb;
    cin >> sumb;

    for (int i = 0; i < 9; i++) {
        int x;
        cin >> x;
        sumb -= x;
    }

    cout << sumb << '\n';
}