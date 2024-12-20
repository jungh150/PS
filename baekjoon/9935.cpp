#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s, bomb;
    cin >> s >> bomb;

    stack<char> stk;
    int n = bomb.size();

    for (char c: s) {
        if (c == bomb[n - 1]) {
            for (int i = n - 2; i >= 0; i--) {
                if (stk.empty()) {
                    for (int j = i + 1; j <= n - 1; j++) {
                        stk.push(bomb[j]);
                    }
                    break;
                }
                if (stk.top() == bomb[i]) {
                    stk.pop();
                } else {
                    for (int j = i + 1; j <= n - 1; j++) {
                        stk.push(bomb[j]);
                    }
                    break;
                }
            }
        } else {
            stk.push(c);
        }
    }

    string ans = "";
    while (!stk.empty()) {
        ans += stk.top();
        stk.pop();
    }
    
    if (ans == "") {
        cout << "FRULA\n";
    } else {
        reverse(ans.begin(), ans.end());
        cout << ans << '\n';
    }
}