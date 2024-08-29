#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;
    int apb[26] = {0};

    for (char c: str) apb[c - 'a']++;

    for (int x: apb) cout << x << ' ';
    cout << '\n';
}