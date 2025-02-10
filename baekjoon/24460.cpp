#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> a;

// i: 시작 행 인덱스, j: 시작 열 인덱스
// k: 한 변의 길이
int spc(int i, int j, int k) {
    // 하나라면 그 값 반환
    if (k == 1) return a[i][j];

    int nowk = k / 2;
    int candidate[4];

    // 4개의 구역에서 각각 후보 구하기
    candidate[0] = spc(i, j, nowk);  // 왼쪽 위
    candidate[1] = spc(i, j + nowk, nowk);  // 오른쪽 위
    candidate[2] = spc(i + nowk, j, nowk);  // 왼쪽 아래
    candidate[3] = spc(i + nowk, j + nowk, nowk);  // 오른쪽 아래

    // 후보 정렬
    sort(candidate, candidate + 4);

    // 두 번째로 작은 값 반환
    return candidate[1];
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

    cout << spc(0, 0, n) << '\n';
}