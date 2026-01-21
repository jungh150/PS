#include <iostream>
#include <vector>
using namespace std;

void solve(int b, int p) {
    vector<int> c(b); // 다리를 동시에 건널 수 있는 사람 수
    vector<int> t(b); // 다리를 건너는데 드는 시간
    for (int i = 0; i < b; i++) cin >> c[i] >> t[i];

    vector<vector<int>> br(b, vector<int>(3, 0));
    // br[i][0]: 다리를 건너기 위해 기다리고 있는 사람 수
    // br[i][1]: 다리를 건너고 있는 사람 수
    // br[i][2]: 다리를 다 건너는데 남은 시간

    br[0][0] = p;
    int time = 0;
    while (1) {
        bool fin = true;

        for (int i = b - 1; i >= 0; i--) { // 다리를 뒤에서부터 보기
            if (br[i][1] > 0) { // 건너고 있는 사람이 있다면
                fin = false;
                br[i][2]--;
                if (br[i][2] == 0) {
                    if (i + 1 < b) br[i + 1][0] += br[i][1];
                    br[i][1] = 0;
                }
            }
        }

        for (int i = b - 1; i >= 0; i--) { // 다리를 뒤에서부터 보기
            if (br[i][0] > 0 && br[i][1] == 0) { // 기다리는 사람이 있고 건너고 있는 사람이 없다면
                fin = false;
                int tmp = min(c[i], br[i][0]);
                br[i][0] -= tmp;
                br[i][1] = tmp;
                br[i][2] = t[i];
            }
        }
    
        if (fin) break;
        time++;
    }

    cout << time - 1 << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int b, p;
    while (1) {
        cin >> b >> p;
        if (b == 0 && p == 0) return 0;
        solve(-b, p);
    }
}