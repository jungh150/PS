#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n[3];
    cin >> n[0] >> n[1] >> n[2];

    sort(n, n + 3);

    cout << n[1] << '\n';
}