#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, x;
    cin >> n >> x;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int sumt = 0;
    int s = 0;
    int e = 0;
    // 길이가 x일인 첫번째 구간
    while (e < x) {
        sumt += a[e];
        e++;
    }

    int maxt = sumt;
    int cnt = 1;

    while (e < n) {
        // 한칸씩 뒤로 이동하여 구간의 길이 유지
        sumt -= a[s];
        s++;
        sumt += a[e];
        e++;

        if (sumt > maxt) { // 최댓값이 갱신되면 cnt도 갱신
            maxt = sumt;
            cnt = 1;
        } else if (sumt == maxt) { // 아니라면 cnt만 1 증가
            cnt++;
        }
    }

    if (maxt == 0) cout << "SAD\n";
    else cout << maxt << '\n' << cnt << '\n';
}