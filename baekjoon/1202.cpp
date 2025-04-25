#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;
    
    vector<pair<int, int>> gem(n);
    for (int i = 0; i < n; i++) cin >> gem[i].first >> gem[i].second;

    vector<int> bag(k);
    for (int i = 0; i < k; i++) cin >> bag[i];

    sort(gem.begin(), gem.end()); // 보석 무게 기준 오름차순 정렬
    sort(bag.begin(), bag.end()); // 가방 오름차순 정렬

    long long ans = 0;
    priority_queue<int> q;

    int gi = 0;
    for (int i = 0; i < k; i++) { // 작은 가방부터 하나씩 체크
        // 담을 수 있는 보석을 우선순위 큐에 추가해주기
        while (gi < n && gem[gi].first <= bag[i]) {
            q.push(gem[gi].second);
            gi++;
        }
        // 그 중 가장 가치가 큰 보석을 가방에 넣기
        if (!q.empty()) {
            ans += q.top();
            q.pop();
        }
    }

    cout << ans << '\n';
}