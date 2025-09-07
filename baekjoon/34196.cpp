#include <iostream>
#include <vector>
using namespace std;

vector<vector<bool>> solved(6);
vector<vector<int>> cnt(6);

void solve() {
    int r;
    char c;
    cin >> r >> c;
    if (solved[r][c - 'A']) cout << "Yes ";
    else cout << "No ";
    cout << cnt[r][c - 'A'] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solved[1] = {true, true, true, true, false, true, true, true, true, true, true, true, true};
    solved[2] = {true, true, true, true, false, true, true, true, true, true, true, true, true};
    solved[3] = {true, true, true, true, false, true, false, true, true, true, true, true, true};
    solved[4] = {true, true, true, true, false, true, false, true, true, true, true, true, true};
    solved[5] = {true, true, true, true, false, true, false, true, true, true, true, true, true};
    cnt[1] = {0, 0, 0, 2, 1, 0, 2, 0, 0, 3, 2, 1, 0};
    cnt[2] = {0, 1, 0, 0, 8, 0, 4, 3, 2, 0, 2, 3, 3};
    cnt[3] = {0, 0, 0, 1, 1, 0, 2, 3, 0, 0, 1, 1, 0};
    cnt[4] = {0, 0, 0, 3, 0, 0, 0, 0, 1, 0, 1, 1, 0};
    cnt[5] = {0, 1, 1, 0, 0, 0, 0, 6, 4, 0, 1, 0, 1};

    int T = 1;
    cin >> T;
    for (int i = 0; i < T; i++) {
        solve();
    }
}