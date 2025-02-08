#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m, b;
    cin >> n >> m >> b;

    vector<vector<int>> data(n, vector<int>(m));
    int minHeight = 256, maxHeight = 0;

    // 기존의 땅의 높이 입력받기
    // 입력을 받으면서 최대, 최소 높이 탐색
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> data[i][j];
            minHeight = min(minHeight, data[i][j]);
            maxHeight = max(maxHeight, data[i][j]);
        }
    }

    // mint: 최적 시간, minh: 최적 높이
    // tmp: 작업 시간, lack: 부족한 블록 수, over: 제거할 블록 수
    int mint = 1e9, minh, tmp, lack, over;

    // minHeight ~ maxHeight 범위 내 모든 높이 탐색
    for (int h = minHeight; h <= maxHeight; h++) {
        lack = over = 0;
        // 지도 전체를 순회하며 블록 높이를 h로 맞추는 데 필요한 블록 계산
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (data[i][j] > h)  // 현재 블록 높이가 목표 높이보다 높다면
                    over += data[i][j] - h;  // 제거해야 할 블록 개수 증가
                else  // 현재 블록 높이가 목표 높이보다 낮다면
                    lack += h - data[i][j];  // 추가로 필요한 블록 개수 증가
            }
        }

        // 부족한 블록이 {제거된 블록 + 인벤토리 블록}보다 많으면 불가능
        if (lack <= over + b) {
            tmp = over * 2 + lack;
            // 최소 시간 갱신 (시간이 같다면 더 높은 높이를 선택)
            if (tmp <= mint) {
                mint = tmp;
                minh = h;
            }
        }
    }

    // 최적의 시간과 땅 높이 출력
    cout << mint << ' ' << minh << '\n';
}