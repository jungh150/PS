#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;

    for (char c: s) cout << (char) (c + 'A' - 'a');
    cout << '\n';
}