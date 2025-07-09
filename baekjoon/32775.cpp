#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int s, f;
    cin >> s >> f;

    if (f < s) cout << "flight\n";
    else cout << "high speed rail\n";
}