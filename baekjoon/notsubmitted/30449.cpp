#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

// 미해결

struct compare {
    bool operator() (pair<int, int> &a, pair<int, int> &b) {
        return a.first * b.second < b.first * a.second;
    }
};

void solve() {
    int n, k;
    cin >> n >> k;

    priority_queue<pair<int, int>, vector<pair<int, int>>, compare> pq;
    
    pq.push({0, 1});
    if (pq.size() > k) pq.pop();
    pq.push({1, 1});
    if (pq.size() > k) pq.pop();

    for (int i = 2; i <= n; i++) { // 분모
        for (int j = 1; j < i; j++) { // 분자
            if (__gcd(i, j) > 1) continue;
            pq.push({j, i});
            if (pq.size() > k) pq.pop();
        }
    }

    cout << pq.top().first << ' ' << pq.top().second << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}