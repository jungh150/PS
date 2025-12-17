#include <iostream>
#include <vector>
using namespace std;

string d[] = {"####.##.##.####",  // 0
              "..#..#..#..#..#",  // 1
              "###..#####..###",  // 2
              "###..####..####",  // 3
              "#.##.####..#..#",  // 4
              "####..###..####",  // 5
              "####..####.####",  // 6
              "###..#..#..#..#",  // 7
              "####.#####.####",  // 8
              "####.####..####"}; // 9

void solve() {
    vector<string> s(4, "");

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            string tmp;
            cin >> tmp;
            s[j] += tmp;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (i == 2) cout << ":";
        for (int j = 0; j < 10; j++) {
            bool psb = true;
            for (int k = 0; k < 15; k++) {
                if (d[j][k] == '.' && s[i][k] == '#') {
                    psb = false;
                    break;
                }
            }
            if (psb) {
                cout << j;
                break;
            }
        }
    }
    cout << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T = 1;
    for (int i = 0; i < T; i++) {
        solve();
    }
}