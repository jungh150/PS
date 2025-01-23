#include <iostream>
#include <stack>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    stack<pair<int, int>> s;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;

        while (!s.empty() && s.top().second < x) {
            s.pop();
        }

        if (s.empty()) cout << 0 << ' ';
        else cout << s.top().first << ' ';

        s.emplace(i, x);
    }

    cout << '\n';
}