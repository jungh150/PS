#include <iostream>
#include <stack>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        string ans = "YES\n";
        stack<char> stk;
        string s;
        cin >> s;

        for (char c: s) {
            // 왼쪽 괄호면 스택에 넣기
            // 오른쪽 괄호면 스택에서 맨 위 하나를 꺼내서 확인
            //              꺼낼 수 없으면 (오른쪽 괄호가 남으면) "NO"
            if (c == '(') {
                stk.push(c);
            } else if (c == ')') {
                if (stk.empty()) {
                    ans = "NO\n";
                    break;
                } else {
                    stk.pop();
                }
            }
        }

        // 스택이 비어있지 않다면 (왼쪽 괄호가 남으면) "NO"
        if (!stk.empty()) ans = "NO\n";
        cout << ans;
    }
}