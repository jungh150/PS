#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    if (n == 0) cout << 1 << '\n';
    else if (n == 1) cout << 2 << '\n';
    else if (n == 2) cout << 1 << '\n';
    else cout << 0 << '\n';
}