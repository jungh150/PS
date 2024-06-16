#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};
int n, m;
vector<vector<int>> og;
vector<vector<int>> g;
vector<vector<bool>> vst;

bool chk() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 1) return false;
        }
    }
    return true;
}

void init_g() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            g[i][j] = og[i][j];
        }
    }
}

void init_vst() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            vst[i][j] = false;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    og = vector<vector<int>>(n, vector<int>(m));
    g = vector<vector<int>>(n, vector<int>(m));
    vst = vector<vector<bool>>(n, vector<bool>(m));

    for (int i = 0; i < n; i++) {
        string tmp;
        cin >> tmp;
        for (int j = 0; j < m; j++) {
            og[i][j] = tmp[j] - '0';
        }
    }

    int mina = 10000;
    int cnt = 0;

    init_g();
    init_vst();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 1) continue;
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < m; l++) {
                    init_g();
                    init_vst();
                    if (g[k][l] == 1) continue;
                    if (k == i && l == j) continue;
                    cnt = 0;
                    queue<pair<int, int>> q;
                    q.emplace(i, j);
                    q.emplace(k, l);
                    vst[i][j] = vst[k][l] = true;
                    while (!q.empty()) {
                        if (chk()) break;
                        cnt++;
                        int qsize = q.size();
                        for (int x = 0; x < qsize; x++) {
                            auto [a, b] = q.front();
                            q.pop();
                            int ta, tb;
                            for (int d = 0; d < 4; d++) {
                                ta = a + dx[d];
                                tb = b + dy[d];
                                if (ta >= 0 && ta < n && tb >= 0 && tb < m) {
                                    if (!vst[ta][tb]) {
                                        g[ta][tb] = 0;
                                        q.emplace(ta, tb);
                                        vst[ta][tb] = true;
                                    }
                                }
                            }
                        }
                    }
                    if (cnt < mina) mina = cnt;
                }
            }
        }
    }

    cout << mina << '\n';
}