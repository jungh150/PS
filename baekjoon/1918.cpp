#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// 연산자의 우선 순위
int prec(char c) {
    if (c == '(' || c == ')') return 0;
    else if (c == '+' || c == '-') return 1;
    else if (c == '*' || c == '/') return 2;
    else return 3;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    stack<char> stk;

    string s;
    cin >> s;

    for (char c: s) {
        if (c >= 'A' && c <= 'Z') {
            cout << c;
        } else if (c == '(') {
            stk.push(c);
        } else if (c == ')') {
            while (stk.top() != '(') {
                cout << stk.top();
                stk.pop();
            }
            stk.pop();
        } else {
            while (!stk.empty() && prec(c) <= prec(stk.top())) {
                cout << stk.top();
                stk.pop();
            }
            stk.push(c);
        }
    }

    while (!stk.empty()) {
        cout << stk.top();
        stk.pop();
    }

    cout << '\n';
}