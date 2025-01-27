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
        // x: 현재 탑의 높이
        int x;
        cin >> x;

        // 현재 탑 높이보다 낮은 것들 스택에서 전부 빼기
        while (!s.empty() && s.top().second < x) {
            s.pop();
        }

        // 현재 탑에서 발사한 레이저가 신호를 수신하는 탑은
        // 현재 탑에서 왼쪽으로 이동하면서 볼 때, 자신보다 높이가 높은 탑 중 처음 만나는 탑
        if (s.empty()) cout << 0 << ' ';
        else cout << s.top().first << ' ';

        s.emplace(i, x);
    }

    cout << '\n';
}