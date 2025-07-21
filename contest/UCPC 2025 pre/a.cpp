#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a, b, c, d;
    cin >> a >> b >> c >> d;

    if (a + b + c + d + 300 <= 1800) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}