#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    cout << n * 0.78 << '\n' << n * 0.8 + n * 0.2 * 0.78 << '\n';
}