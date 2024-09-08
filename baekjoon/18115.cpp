#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> ac(n);
    for (int i = 0; i < n; i++) cin >> ac[i];

    deque<int> dq;
    for (int i = n - 1; i >= 0; i--) {
        if (ac[i] == 1) {
            dq.push_front(n - i);
        } else if (ac[i] == 2) {
            int tmp = dq.front();
            dq.pop_front();
            dq.push_front(n - i);
            dq.push_front(tmp);
        } else if (ac[i] == 3) {
            dq.push_back(n - i);
        }
    }

    for (int i = 0; i < n; i++) {
        cout << dq.front() << ' ';
        dq.pop_front();
    }
    cout << '\n';
}