#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int>> a;

int scdmax(int a, int b, int c, int d) {
    priority_queue<int> q;
    q.push(a);
    q.push(b);
    q.push(c);
    q.push(d);
    q.pop();
    return q.top();
}

int pool(int si, int sj, int curn) {
    if (curn == 1) {
        return a[si][sj];
    }
    int ei = si + curn;
    int ej = ei + curn;
    int a = pool(si, sj, curn / 2);
    int b = pool(si, sj + curn / 2, curn / 2);
    int c = pool(si + curn / 2, sj, curn / 2);
    int d = pool(si + curn / 2, sj + curn / 2, curn / 2);
    return scdmax(a, b, c, d);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    a = vector<vector<int>>(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    cout << pool(0, 0, n) << '\n';
}