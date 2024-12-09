#include <iostream>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;

    int maxh = 0;
    priority_queue<pair<int, int>> pq;
    
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        maxh = max(maxh, a);
        maxh = max(maxh, b);
        pq.emplace(-a, i);
        pq.emplace(-b, i);
    }

    while (n > 1) {
        int h = -pq.top().first;
        int p = pq.top().second;
        pq.pop();
        maxh++;
        h = maxh;
        pq.emplace(-h, p);
        n--;
    }

    cout << pq.top().second << '\n';
}