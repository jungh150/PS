#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int n;
        string str;
        cin >> n >> str;

        str.erase(n - 1, 1);
        cout << str << '\n';
    }
}