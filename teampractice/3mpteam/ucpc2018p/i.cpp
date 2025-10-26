#include <iostream>
#include <vector>
using namespace std;

int n;
vector<vector<int>> gmi1;
vector<vector<int>> gmi2;
vector<vector<char>> gmc1;
vector<vector<char>> gmc2;
vector<vector<vector<int>>> ingi;
vector<vector<string>> ingc;

int dx[] = {0, 0, 1, 1};
int dy[] = {0, 1, 0, 1};

void dfs(int cnt, int idx) {
    if (cnt == n) {
        // 계산
        return;
    }
    for (int i = idx + 1; i < n; i++) { // 재료
        for (int j = 0; j < 4; j++) { // 위치
            // 0도
            gmi2 = vector<vector<int>>(5, vector<int>(5, 0));
            gmc2 = vector<vector<char>>(5, vector<char>(5, 'W'));
            for (int x = 0; x < 4; x++) {
                for (int y = 0; y < 4; y++) {
                    // 효능
                    gmi2[x + dx[j]][y + dy[j]] += ingi[i][x][y];
                    if (gmi2[x + dx[j]][y + dy[j]] > 9) gmi2[x + dx[j]][y + dy[j]] = 9;
                    else if (gmi2[x + dx[j]][y + dy[j]] < 0) gmi2[x + dx[j]][y + dy[j]] = 0;
                    // 원소
                    if (ingc[i][x][y] != 'W') gmc2[x + dx[j]][y + dy[j]] = ingc[i][x][y];
                }
            }
            // 90도
            gmi2 = vector<vector<int>>(5, vector<int>(5, 0));
            gmc2 = vector<vector<char>>(5, vector<char>(5, 'W'));
            for (int x = 0; x < 4; x++) {
                for (int y = 0; y < 4; y++) {
                    // 효능
                    gmi2[x + dx[j]][y + dy[j]] += ingi[i][x][y];
                    if (gmi2[x + dx[j]][y + dy[j]] > 9) gmi2[x + dx[j]][y + dy[j]] = 9;
                    else if (gmi2[x + dx[j]][y + dy[j]] < 0) gmi2[x + dx[j]][y + dy[j]] = 0;
                    // 원소
                    if (ingc[i][x][y] != 'W') gmc2[x + dx[j]][y + dy[j]] = ingc[i][x][y];
                }
            }
            // 180도

            // 270도
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;

    gmi1 = vector<vector<int>>(5, vector<int>(5, 0));
    gmc1 = vector<vector<char>>(5, vector<char>(5, 'W'));

    ingi = vector<vector<vector<int>>>(n, vector<vector<int>>(4, vector<int>(4)));
    ingc = vector<vector<string>>(n, vector<string>(4));

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) cin >> ingi[k][i][j];
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < 4; i++) cin >> ingc[k][i];
    }
}