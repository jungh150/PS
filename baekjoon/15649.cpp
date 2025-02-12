#include <iostream>
#include <vector>
using namespace std;

int n, m;
vector<int> ans;  // 현재까지 선택된 숫자를 저장하는 배열
vector<bool> chk;  // 숫자 사용 여부를 체크하는 배열

void dfs(int idx) {
    // m개의 숫자를 모두 선택한 경우
    if (idx == m) {
        for (int x: ans) cout << x << ' ';
        cout << '\n';
        return;
    }

    // 1부터 n까지의 숫자를 탐색하며 선택
    for (int i = 1; i < n + 1; i++) {
        if (!chk[i]) {  // 아직 선택되지 않은 숫자라면
            chk[i] = true;  // 숫자 i를 선택했다고 표시
            ans[idx] = i;  // 현재 위치(idx)에 i 저장
            dfs(idx + 1);  // 다음 위치(idx+1)로 이동하여 재귀 호출
            chk[i] = false;  // 다시 이전으로 복구
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    ans = vector<int>(m);
    chk = vector<bool>(n + 1);

    dfs(0);
}