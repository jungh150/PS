#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    for (int i = 0; i < 2; i++) {
        int t, f, s, p, c;
        cin >> t >> f >> s >> p >> c;
        
        cout << 6 * t + 3 * f + 2 * s + p + 2 * c << ' ';
    }
    cout << '\n';
}