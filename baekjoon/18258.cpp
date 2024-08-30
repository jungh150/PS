#include <iostream>
#include <deque>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    deque<int> deq;

    while(n--) {
        string s;
        cin >> s;
        if (s == "push") {
            int x;
            cin >> x;
            deq.push_back(x);
        } else if (s == "pop") {
            if (deq.empty()) {
                cout << -1 << '\n';
            } else {
                cout << deq.front() << '\n';
                deq.pop_front();
            }
        } else if (s == "size") {
            cout << deq.size() << '\n';
        } else if (s == "empty") {
            if (deq.empty()) cout << 1 << '\n';
            else cout << 0 << '\n';
        } else if (s == "front") {
            if (deq.empty()) cout << -1 << '\n';
            else cout << deq.front() << '\n';
        } else if (s == "back") {
            if (deq.empty()) cout << -1 << '\n';
            else cout << deq.back() << '\n';
        }
    }
}