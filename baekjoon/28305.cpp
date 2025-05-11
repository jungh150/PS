#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, t;
    cin >> n >> t;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    sort(a.begin(), a.end());

    int l = 0;
    int r = n + 1;
    while (l < r) {
        int m = (l + r) / 2; // 세미나실의 개수에 대해서 이분탐색

        int curt = 0; // 현재 시간
        int cnt = 0; // 현재 시간 기준 사용 중인 세미나실의 개수
        queue<int> q; // 끝나는 시간 넣어두는 큐
        bool psb = true;

        for (int i = 0; i < n; i++) {
            curt = max(a[i] - t + 1, 1);
            if (cnt == m) {
                if (q.empty() || q.front() >= a[i]) {
                    psb = false;
                    break;
                }
                int tmp = max(curt, q.front() + 1);
                q.pop();
                q.push(tmp + t - 1);
            } else {
                q.push(curt + t - 1);
                cnt++;
            }
        }

        if (!psb) l = m + 1;
        else r = m;
    }

    cout << l << '\n';
}