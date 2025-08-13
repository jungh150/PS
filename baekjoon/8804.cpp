#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int z;
    cin >> z;

    while (z--) {
        string s;
        cin >> s;
        bool isPalindrome = true;
        int n = s.size();
        for (int i = 0; i < n / 2 + 1; i++) {
            if (s[i] != s[n - i - 1]) {
                isPalindrome = false;
                break;
            }
        }
        if (isPalindrome) cout << 1 << '\n';
        else cout << 2 << '\n';
    }
}