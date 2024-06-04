#include <iostream>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string str;
    int cnt = 0;

    while (true) {
        cnt = 0;
        getline(cin, str);
        if (str == "#") {
            break;
        }
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u'
                || str[i] == 'A' || str[i] == 'E' || str[i] == 'I' || str[i] == 'O' || str[i] == 'U') {
                cnt++;
            }
        }
        cout << cnt << '\n';
    }
}