#include <bits/stdc++.h>
using namespace std;

int n;
int as;
vector<vector<char>> a;
vector<vector<int>> cnt;
bool flag = false;

bool cntchk(int i, int j) {
    vector<int> tmpcnt(3, n);
    for (int k = 0; k <= i; k++) {
        if (a[k][j] == 'A') {
            tmpcnt[0]--;
            if (tmpcnt[0] < 0) return false;
        } else if (a[k][j] == 'N') {
            tmpcnt[1]--;
            if (tmpcnt[1] < 0) return false;
        } else if (a[k][j] == 'K') {
            tmpcnt[2]--;
            if (tmpcnt[2] < 0) return false;
        } 
    }
    return true;
}

bool psb(int i, int j) {
    if (i >= 2) {
        if (j >= 2) {
            if (a[i][j - 1] == 'N' && a[i][j - 2] == 'A') return false;
            if (a[i - 1][j - 1] == 'N' && a[i - 2][j - 2] == 'A') return false;
        }
        if (a[i - 1][j] == 'N' && a[i - 2][j] == 'A') return false;
    } else {
        if (j >= 2) {
            if (a[i][j - 1] == 'N' && a[i][j - 2] == 'A') return false;
        }
    }
    return true;
}

bool dfs(int curi, int curj) {
    if (curi == as) {
        flag = true;
        return true;
    }

    int nxti = curi;
    int nxtj = curj + 1;
    if (nxtj == as) {
        nxti++;
        nxtj = 0;
    }

    // a
    if (cnt[curi][0] > 0) {
        cnt[curi][0]--;
        a[curi][curj] = 'A';
        if (cntchk(curi, curj)) dfs(nxti, nxtj);
        cnt[curi][0]++;
    }

    if (flag) return true;

    // n
    if (cnt[curi][1] > 0) {
        cnt[curi][1]--;
        a[curi][curj] = 'N';
        if (cntchk(curi, curj)) dfs(nxti, nxtj);
        cnt[curi][1]++;
    }

    if (flag) return true;

    // z
    if (cnt[curi][2] > 0) {
        cnt[curi][2]--;
        a[curi][curj] = 'Z';
        if (psb(curi, curj)) {
            if (cntchk(curi, curj)) dfs(nxti, nxtj);
        }
        cnt[curi][2]++;
    }

    if (flag) return true;
    else return false;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> n;
    as = n * 3;

    a = vector<vector<char>>(as, vector<char>(as));
    cnt = vector<vector<int>>(as, vector<int>(3, n));

    if (dfs(0, 0)) {
        for (int i = 0; i < as; i++) {
            for (int j = 0; j < as; j++) {
                cout << a[i][j];
            }
            cout << '\n';
        }
    } else {
        cout << -1 << '\n';
    }
}