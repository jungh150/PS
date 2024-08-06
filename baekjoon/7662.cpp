#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;
    cin >> t;

    while (t--) {
        int k;
        cin >> k;
        int cnt = 0;
        priority_queue<long long> maxq;
        priority_queue<long long> maxdq;
        priority_queue<long long> minq;
        priority_queue<long long> mindq;

        while (k--) {
            char op;
            long long x;
            cin >> op >> x;
            if (op == 'I') {
                maxq.push(x);
                minq.push(-x);
                cnt++;
            } else if (op == 'D' && x == 1) {
                if (cnt > 0) {
                    while (!maxdq.empty() && maxdq.top() == maxq.top()) {
                        maxdq.pop();
                        maxq.pop();
                    }
                    mindq.push(-maxq.top());
                    maxq.pop();
                    cnt--;
                }
            } else if (op == 'D' && x == -1) {
                if (cnt > 0) {
                    while (!mindq.empty() && mindq.top() == minq.top()) {
                        mindq.pop();
                        minq.pop();
                    }
                    maxdq.push(-minq.top());
                    minq.pop();
                    cnt--;
                }
            }
        }

        while (!maxdq.empty() && maxdq.top() == maxq.top()) {
            maxdq.pop();
            maxq.pop();
        }
        while (!mindq.empty() && mindq.top() == minq.top()) {
            mindq.pop();
            minq.pop();
        }

        if (cnt == 0) cout << "EMPTY\n";
        else cout << maxq.top() << ' ' << -minq.top() << '\n';
    }
}