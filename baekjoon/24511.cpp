#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // n: 자료구조의 개수
    int n;
    cin >> n;

    // q: 큐
    queue<int> q;

    vector<int> a(n);
    vector<int> b(n);

    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    for (int i = n - 1; i >= 0; i--) {
        if (a[i] == 0) q.push(b[i]);
    }

    // m: 삽입할 수열의 길이
    int m;
    cin >> m;

    while (m--) {
        int x;
        cin >> x;

        q.push(x);
        cout << q.front() << ' ';
        q.pop();
    }
    cout << '\n';
}