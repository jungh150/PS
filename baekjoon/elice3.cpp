#include <iostream>
#include <stack>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;

    stack<char> stk;
    for (char c: s) {
        if (c == ')') {
            stk.pop()...
        } else {
            stk.push(c);
        }
    }
}