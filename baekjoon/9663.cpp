#include <iostream>
#include <vector>
#include <set>
using namespace std;

int n;  // 체스판 크기
vector<int> col;  // col[i]: i번째 행에서 퀸이 위치한 열 번호
int cnt = 0;  // 가능한 퀸 배치 경우의 수

// 현재 퀸 배치가 유망한지 확인하는 함수
bool promising(int idx) {
    for (int k = 0; k < idx; k++) {
        // 같은 열(col[idx] == col[k]) 또는 대각선(|col[idx] - col[k]| == |idx - k|)
        if (col[idx] == col[k] || abs(col[idx] - col[k]) == (idx - k)) {
            return false;  // 충돌 발생 시 False 반환
        }
    }
    return true;
}

// 백트래킹을 이용해 퀸을 배치하는 함수
void dfs(int idx) {
    // 모든 퀸을 배치한 경우
    if (idx == n) {
        cnt++;
    } else {
        // 현재 행(idx)에 퀸을 놓을 수 있는 모든 열을 탐색
        for (int j = 0; j < n; j++) {
            col[idx] = j;  // 퀸을 j번째 열에 배치
            if (promising(idx)) {
                dfs(idx + 1);
            }
            col[idx] = -1;  // 원상 복구
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    col = vector<int>(n, -1);

    dfs(0);

    cout << cnt << '\n';
}