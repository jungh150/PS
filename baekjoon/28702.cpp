#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int ans;
    for (int i = 3; i > 0; i--) {
        string str;
        cin >> str;
        if (str[0] != 'F' && str[0] != 'B') {
            ans = stoi(str) + i;
        }
    }

    if (ans % 3 == 0) {
        if (ans % 5 == 0) {
            cout << "FizzBuzz\n";
        } else {
            cout << "Fizz\n";
        }
    } else {
        if (ans % 5 == 0) {
            cout << "Buzz\n";
        } else {
            cout << ans << "\n";
        }
    }
}