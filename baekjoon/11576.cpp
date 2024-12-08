#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a, b, m;
    cin >> a >> b >> m;

    vector<int> arr(m);
    for (int i = 0; i < m; i++) cin >> arr[i];

    int ans = 0;
    int tmp = 1;

    for (int i = m - 1; i >= 0; i--) {
        ans += arr[i] * tmp;
        tmp *= a;
    }

    stack<int> stk;
    while (ans != 0) {
        stk.push(ans % b);
        ans /= b;
    }

    while (!stk.empty()) {
        cout << stk.top() << ' ';
        stk.pop();
    }
    cout << '\n';
}