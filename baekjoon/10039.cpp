#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int s[5];
    int total = 0;
    for (int i = 0; i < 5; i++) {
        int x;
        cin >> x;
        total += max(40, x);
    }

    cout << total / 5 << '\n';
}