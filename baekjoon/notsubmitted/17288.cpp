#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    cin >> str;

    int cnt = 0;
    int pre = -1;

    int total = 0;
    for (char c: str) {
        if (pre == -1 || pre + 1 == c - '0') {
            cnt++;
        } else {
            if (cnt == 3) total++;
            cnt = 1;
        }
        pre = c - '0';
    }
    if (cnt == 3) total++;

    cout << total << '\n';
}