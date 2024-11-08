#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string addBigNum(string a, string b) {
    int carry = 0;
    string res = "";

    while (!a.empty() || !b.empty() || carry) {
        if (!a.empty()) {
            carry += a.back() - '0';
            a.pop_back();
        }
        if (!b.empty()) {
            carry += b.back() - '0';
            b.pop_back();
        }

        res += ((carry % 10) + '0');
        carry /= 10;
    }

    reverse(res.begin(), res.end());
    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    
    vector<string> fib(n + 1);
    fib[0] = "0";
    if (n != 0) fib[1] = "1";
    for (int i = 2; i < n + 1; i++) {
        fib[i] = addBigNum(fib[i - 1], fib[i - 2]);
    }

    cout << fib[n] << '\n';
}