#include <iostream>
#include <map>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t;  // 테스트 케이스 개수
    cin >> t;

    while (t--) {
        int n;  // 의상 개수
        cin >> n;
        map<string, int> m;  // 아이템 종류별 개수를 저장할 맵
        int ans = 1;  // 조합 수 계산을 위한 변수 (곱셈이므로 초기값 1)
        while (n--) {
            string name, type;
            cin >> name >> type;
            if (m.find(type) == m.end()) m.insert({type, 1});  // 새로운 종류이면 초기값 1 삽입
            else m[type]++;  // 기존 종류이면 개수 증가
        }
        for (auto x: m) {
            ans *= x.second + 1;  // 의상 개수 + 1 (선택하지 않는 경우) 곱하기
        }
        cout << ans - 1 << '\n';  // 알몸인 경우 제외
    }
}