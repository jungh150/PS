#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, a, b;
    cin >> n >> a >> b;

    if (n > b) {
        cout << "Bus\n";
    } else {
        if (a == b) cout << "Anything\n";
        else if (a > b) cout << "Subway\n";
        else if (a < b) cout << "Bus\n";
    }
}