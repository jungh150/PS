#include <iostream>
#include <vector>
using namespace std;

int rainbow[] = {17, 14, 24, 6, 1, 8, 21};
bool upper[26];
bool lower[26];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    string s;
    cin >> s;

    for (char c: s) {
        if (c <= 'Z') upper[c - 'A'] = true;
        else lower[c - 'a'] = true;
    }

    bool upperPsb = 1;
    bool lowerPsb = 1;
    for (int i = 0; i < 7; i++) {
        if (!upper[rainbow[i]]) {
            upperPsb = 0;
            break;
        }
    }
    for (int i = 0; i < 7; i++) {
        if (!lower[rainbow[i]]) {
            lowerPsb = 0;
            break;
        }
    }

    if (upperPsb && lowerPsb) cout << "YeS\n";
    else if (upperPsb) cout << "YES\n";
    else if (lowerPsb) cout << "yes\n";
    else cout << "NO!\n";
}