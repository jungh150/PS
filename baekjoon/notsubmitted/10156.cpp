#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int k, n ,m;
    cin >> k >> n >> m;

    cout << max(0, k * n - m) << '\n';
}