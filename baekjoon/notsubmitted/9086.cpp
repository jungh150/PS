#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        string str;
        cin >> str;
        cout << str[0] << str[str.size() - 1] << '\n';
    }
}