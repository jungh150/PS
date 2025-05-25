#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    string s;
    cin >> s;

    if (s[0] == 'B' || s[n - 1] == 'A') cout << "No\n";
    else cout << "Yes\n";
}