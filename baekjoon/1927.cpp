#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    priority_queue<int, vector<int>, greater<>> pq;

    int n;
    cin >> n;

    for (int t = 0; t < n; t++) {
        int x;
        cin >> x;

        if (x == 0) {
            if (!pq.empty()) {
                cout << pq.top() << '\n';
                pq.pop();
            } else {
                cout << 0 << '\n';
            }
        }
        else {
            pq.push(x);
        }
    }
}