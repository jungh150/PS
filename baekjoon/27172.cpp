#include <iostream>
#include <vector>
using namespace std;

// MAX_SIZE: x의 최댓값 + 1
int const MAX_SIZE = 1000001;
// ex: 특정 수가 플레이어의 카드 중에 있었는지 저장하는 배열
bool ex[MAX_SIZE];
// s: 특정 수의 점수를 저장하는 배열
int s[MAX_SIZE];

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;
    vector<int> x(n);

    for (int i = 0; i < n; i++) {
        cin >> x[i];
        ex[x[i]] = true; // 플레이어 카드 중에 등장했으므로 ex에 체크
    }

    for (int i = 0; i < n; i++) {
        // i번째 카드에 적힌 수의 배수(= j)를 하나씩 확인
        for (int j = x[i] + x[i]; j < MAX_SIZE; j += x[i]) {
            if (ex[j]) { // j가 플레이어 카드 중에 있었다면
                s[x[i]]++; // i번째 카드에 적힌 수의 점수는 + 1
                s[j]--; // j의 점수는 - 1
            }
        }
    }

    for (int i = 0; i < n; i++) cout << s[x[i]] << ' ';
    cout << '\n';
}