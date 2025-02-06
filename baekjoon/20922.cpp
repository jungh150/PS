#include <iostream>
#include <vector>
#include <set>
using namespace std;

int cnt[100001];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int s = 0;
    int e = 0;
    int maxt = 0;
    int cur = 0;

    while (e < n) {
        if (cnt[a[e]] < k) { // a[e]의 개수가 k보다 작다면
            cnt[a[e]]++;
            e++;
            cur++;
        } else { // a[e]의 개수가 k보다 크거나 같다면
            while (a[s] != a[e]) { // a[e]가 나올 때까지 a[s] 삭제 후 a 이동
                cnt[a[s]]--;
                s++;
                cur--;
            }
            cnt[a[s]]--;
            s++;
            cnt[a[e]]++;
            e++;
        }

        if (cur > maxt) maxt = cur;
    }

    cout << maxt << '\n';
}