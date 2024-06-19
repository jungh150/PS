#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n, k;
    cin >> n >> k;

    int da[3] = {0, 0, 1};
    int db[3] = {1, -1, k};

    vector<vector<bool>> vst(2, vector<bool>(n + 1, false));
    vector<vector<bool>> l(2, vector<bool>(n + 1, false));
    string tmp;

    for (int i = 0; i < 2; i++) {
        cin >> tmp;
        for (int j = 1; j < n + 1; j++) {
            if (tmp[j - 1] == '1') l[i][j] = true;
        }
    }

    int cnt = 0;

    queue<pair<int, int>> q;
    q.emplace(0, 1);
    vst[0][1] = true;
    while (!q.empty()) {
        int tmps = q.size();
        for (int i = 0; i < tmps; i++) {
            auto [a, b] = q.front();
            q.pop();
            if (!l[a][b]) continue;
            for (int di = 0; di < 3; di++) {
                int ta = (a + da[di]) % 2;
                int tb = b + db[di];
                if (tb > n) {
                    cout << "1\n";
                    return 0;
                }
                if (tb <= 0) continue;
                if (vst[ta][tb]) continue;
                if (l[ta][tb]) {
                    q.emplace(ta, tb);
                    vst[ta][tb] = true;
                }
            }
        }
        cnt++;
        if (cnt < n) {
            l[0][cnt] = l[1][cnt] = false;
        }
    }

    cout << "0\n";
}