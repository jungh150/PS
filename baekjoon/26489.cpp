#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int cnt = 0;
    string s;

    while (getline(cin, s)) {
        cnt++;
    }

    cout << cnt << '\n';
}