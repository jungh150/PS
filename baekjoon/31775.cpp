#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int chk[] = {0, 0, 0};
    string str;

    for (int i = 0; i < 3; i++) {
        cin >> str;
        if (str[0] == 'l') {
            chk[0]++;
        } else if (str[0] == 'k') {
            chk[1]++;
        }else if (str[0] == 'p') {
            chk[2]++;
        }
    }

    if ((chk[0] == 1) && (chk[1] == 1) && (chk[2] == 1)) {
        cout << "GLOBAL\n";
    } else {
        cout << "PONIX\n";
    }
}