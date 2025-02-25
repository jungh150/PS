#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t1, t2;
    cin >> t1 >> t2;

    cout << min(t1, t2) << '\n';
}