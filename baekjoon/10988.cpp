#include <iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    bool isPalindrome = true;
    string str;
    cin >> str;

    int n = str.size();
    for (int i = 0; i < n / 2 + 1; i++) {
        if (str[i] != str[n - i - 1]) {
            isPalindrome = false;
        }
    }

    cout << isPalindrome << '\n';
}