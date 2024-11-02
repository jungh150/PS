#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    string s;
    cin >> n;

    getline(cin, s);
    for (int i = 1; i < n + 1; i++) {
        string s;
        getline(cin, s);
        cout << i << ". " << s << '\n';
    }
}