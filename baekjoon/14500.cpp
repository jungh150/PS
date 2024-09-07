#include <iostream>
#include <vector>
using namespace std;

int dx[][3] = {
    {1, 1, 1}, {0, 0, 0},
    {1, 0, -1},
    {0, 0, 1}, {1, 0, 0}, {0, 0, 1}, {1, 0, 0}, 
    {0, 1, 1}, {1, 1, 0}, {0, 1, 1}, {1, 1, 0},
    {0, 1, 0}, {0, -1, 0},
    {-1, 0, -1}, {-1, 0, -1},
    {-1, 1, 1}, {-1, 1, 1}, {1, 0, 0}, {-1, 0, 0}
};

int dy[][3] = {
    {0, 0, 0}, {1, 1, 1},
    {0, 1, 0},
    {-1, -1, 0}, {0, -1, -1}, {1, 1, 0}, {0, 1, 1},
    {1, 0, 0}, {0, 0, 1}, {-1, 0, 0}, {0, 0, -1},
    {-1, 0, -1}, {-1, 0, -1},
    {0, 1, 0}, {0, -1, 0},
    {1, 0, 0}, {-1, 0, 0}, {-1, 1, 1}, {-1, 1, 1}
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
        }
    }
    
    int maxt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 19; k++) {
                int sum = g[i][j];
                int curi = i;
                int curj = j;
                bool psb = true;
                for (int l = 0; l < 3; l++) {
                    curi += dx[k][l];
                    curj += dy[k][l];
                    if (curi < 0 || curi >= n || curj < 0 || curj >= m) {
                        psb = false;
                        break;
                    }
                    sum += g[curi][curj];
                }
                if (psb) {
                    if (sum > maxt) maxt = sum;
                }
            }
        }
    }

    cout << maxt << '\n';
}