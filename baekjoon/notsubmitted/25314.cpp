#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    int cnt = (n + 3) / 4;
    for (int i = 0; i < cnt; i++) cout << "long ";
    cout << "int\n";
}