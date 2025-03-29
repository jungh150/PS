#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int m;
    cin >> m;

    vector<int> b(m);
    for (int i = 0; i < m; i++) cin >> b[i];

    vector<int> ans;

    int amaxi = 0;
    int amax = 0;
    int apremax = 1000;
    int bmaxi = 0;

    while (amaxi < n && bmaxi < m) {
        amax = 0;
        int atmpi = 0;
        bool afound = false;
        bool bfound = false;

        // a에서 최댓값 구하기 (이전에 구한 최댓값 이후 안에서)
        for (int i = amaxi; i < n; i++) {
            if (a[i] > amax && a[i] < apremax) {
                amax = a[i];
                atmpi = i;
                afound = true;
            }
        }

        // 해당 범위에서 찾지 못했으면 a 인덱스 증가하고 continue
        if (!afound) {
            amaxi++;
            continue;
        }

        // 방금 구한 a의 최댓값이 b에도 있는지 체크
        for (int i = bmaxi; i < m; i++) {
            if (b[i] == amax) {
                bmaxi = i + 1;
                ans.push_back(amax);
                amaxi = atmpi + 1;
                bfound = true;
                break;
            }
        }

        // b에서 못 찾았으면 다시 a로 가서 그거보다 작은 값들 중 최댓값 찾기
        if (!bfound) {
            apremax = amax;
        }
    }

    int ansn = ans.size();
    cout << ansn << '\n';
    if (ansn != 0) {
        for (int i = 0; i < ansn; i++) cout << ans[i] << ' ';
        cout << '\n';
    }
}