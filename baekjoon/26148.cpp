#include <iostream>
#include <vector>
using namespace std;

bool leaf(int n) {
    return (((n % 4 == 0) && (n % 100 != 0)) || (n % 400 == 0));
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, d;
    cin >> n >> d;

    if (leaf(n)) cout << "30\n";
    else cout << "29\n";
}