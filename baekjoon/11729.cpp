#include <iostream>
#include <cmath>
using namespace std;

// n: 옮길 원판의 개수
// s: 현재 원판이 있는 탑, e: 원판을 옮길 탑
void recur(int n, int s, int e) {
    if (n == 0) return;
    // ano: s와 e를 제외한 나머지 탑 (거쳐갈 때 필요한 탑)
    int ano = 6 - s - e;

    recur(n - 1, s, ano);
    cout << s << ' ' << e << '\n';
    recur(n - 1, ano, e);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int n;
    cin >> n;

    // 옮긴 횟수: 2^n - 1
    cout << (int) pow(2, n) - 1 << '\n';

    // 수행 과정 출력 by 재귀
    // 원판 5개를 1번 탑에서 3번 탑으로 이동
    recur(n, 1, 3);
}