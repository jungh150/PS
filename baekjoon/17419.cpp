#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    string k;
    cin >> n >> k;

    int cnt = 0;
    for (char c: k) {
        if (c == '1') cnt++;
    }

    cout << cnt << '\n';
}